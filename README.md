# libstd

 String + generic data structures library in C.

## Appendix

This is library written in C that provides easy-to-use implementations of fundamental data structures and a custom string type. It aims to reduce boilerplate and simplify development for C projects that require dynamic arrays, stacks, queues, or hash tables.

## Features

- A custom string type with functions to create, destroy, and query size/capacity.
- Dynamic arrays (vectors)
- Stacks
- Queues
- Hash tables (hashmaps)

## Tech Stack

**Languages:** C

**Build:** Make and Docker

## Installation

Clone the project

```bash
git clone https://codeberg.org/luizvilasboas/libstd.git
```

Go to the project directory

```bash
cd libstd
```

Compile the library

```bash
make
```

Install the library

```bash
sudo make install
```

## Usage/Examples

```c
#include <libstd/data_structures/vector.h>
#include <stdio.h>

int compare_ints(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data_1 = 5, data_2 = 2, data_3 = 8;

    vector_insert(&vector, &data_1);
    vector_insert(&vector, &data_2);
    vector_insert(&vector, &data_3);

    printf("Vector size: %d\n", vector_size(&vector));

    vector_sort(&vector, compare_ints);

    for (size_t i = 0; i < vector_size(&vector); i++) {
        printf("Element %zu: %d\n", i, *(int *)vector_get(&vector, i));
    }

    vector_destroy(&vector);
    return 0;
}
```

## Documentation

[Documentation](#)

## Running Tests

To run tests, run the following command

```bash
make test
```

## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request.

## License

[LGPLv3](https://codeberg.org/luizvilasboas/libstd/src/branch/main/LICENSE)
