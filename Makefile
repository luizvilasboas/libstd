CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -lcheck -lsubunit -lm

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BIN_DIR = bin
LIB_DIR = lib

SRC_SUBDIRS = $(shell find $(SRC_DIR) -type d)
INCLUDE_SUBDIRS = $(shell find $(INCLUDE_DIR) -type d)

SRC = $(shell find $(SRC_DIR) -name '*.c')
TEST_SRC = $(shell find $(TEST_DIR) -name '*_test.c')
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

TEST_BINARIES = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRC))

ALL_SOURCE_FILES = $(shell find $(SRC_DIR) $(TEST_DIR) $(INCLUDE_DIR) -name "*.c" -o -name "*.h")

LIB_NAME = libstd
SHARED_LIB = $(LIB_DIR)/lib$(LIB_NAME).so
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a

PREFIX = /usr/local
INCLUDE_INSTALL_DIR = $(PREFIX)/include
LIB_INSTALL_DIR = $(PREFIX)/lib

all: $(BIN_DIR) $(LIB_DIR) $(SHARED_LIB) $(STATIC_LIB)

$(BIN_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LDFLAGS)

$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $@ $^

$(STATIC_LIB): $(OBJ)
	ar rcs $@ $^

install: all
	mkdir -p $(INCLUDE_INSTALL_DIR)
	mkdir -p $(LIB_INSTALL_DIR)
	@for dir in $(INCLUDE_SUBDIRS); do \
		dest_dir=$(INCLUDE_INSTALL_DIR)/$$(basename $$dir); \
		mkdir -p $$dest_dir; \
		cp $$dir/*.h $$dest_dir 2>/dev/null || true; \
	done
	cp $(SHARED_LIB) $(STATIC_LIB) $(LIB_INSTALL_DIR)

uninstall:
	rm -f $(LIB_INSTALL_DIR)/lib$(LIB_NAME).so
	rm -f $(LIB_INSTALL_DIR)/lib$(LIB_NAME).a
	@for dir in $(INCLUDE_SUBDIRS); do \
		dest_dir=$(INCLUDE_INSTALL_DIR)/$$(basename $$dir); \
		rm -rf $$dest_dir; \
	done

test: $(TEST_BINARIES)
	@for test_bin in $(TEST_BINARIES); do \
		./$$test_bin; \
	done

leak: $(TEST_BINARIES)
	@for test_bin in $(TEST_BINARIES); do \
		valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes  \
			--errors-for-leak-kinds=all \
			$$test_bin; \
	done

format: $(ALL_SOURCE_FILES)
	clang-format -i $(ALL_SOURCE_FILES)

lint: $(ALL_SOURCE_FILES)
	clang-format --dry-run --Werror $(ALL_SOURCE_FILES)

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR)
