<a id="top"></a>

<div align="center">
    <h3>Shopping List</h3>
</div>

---

### Table of Contents

- [Description](#description)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
    - [Basic usage](#basic-usage)
    - [Lists saving](#lists-saving)
    - [Encryption](#encryption)
- [Contributing](#contributing)
- [Acknoledgements](#acknoledgements)
- [License](#license)

---

## Description

Shopping List is a command line program that allows the user to create a shopping list by using an inventory and a "needs" list.

Once started, the program guides the user to create his inventory and his "needs" list. It thens prints him his final shopping list.

The program offers the possibility to store the shopping list in a file.
It also proposes to store the inventory and the "needs" list into files that can be reused when rerunning the program later.

### Built With

[![C](https://skillicons.dev/icons?i=c&theme=light)](https://www.c-language.org/)
[![CMake](https://skillicons.dev/icons?i=cmake&theme=light)](https://cmake.org/)

## Getting Started

### Prerequisites

- CMake
- vcpkg

### Installation

1. Fork the [Project repository](https://github.com/NestorNebula/shopping-list)
2. Clone the forked repository to your local machine
   ```
   git clone git@github.com:<your username>/<repo name>.git
   ```
3. Update remote URL

   ```
   # SSH:
   git remote add upstream git@github.com:NestorNebula/shopping-list.git

   # HTTPS:
   git remote add upstream https://github.com/NestorNebula/shopping-list.git
   ```

4. From the root directory of the project, create the "build" directory
   ```
   cmake -B build/ -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg
   ```
5. Go to the "build" directory created by the previous command and build the program
   ```
   make
   ```
6. Run the program
   ```
   ./shopping-list
   ```

#### Tests

Tests suites can be found in the "tests" directory.

New files in this directory with the extension .cpp will automatically be considered as tests suites.

To run tests, follow this steps:

1. From the root directory of the project, go to the "tests" directory
   ```
   cd tests
   ```
2. Create the "build" directory
   ```
   cmake -B build/ -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg
   ```
3. Go to the "build" directory created by the previous command and build the test file
   ```
   make
   ```
4. Run the tests
   ```
   ./shopping-list-tests
   ```

## Usage

### Basic usage

Once the program is running, it guides the user to create its inventory and "needs" list.
"Items" can be added to both and both lists will be compared on the moment to create the shopping list.

Items are unique by their name, meaning that it isn't possible for two items in the list to have the same name, but also that the comparison between the lists is done by name search. Thus a typo in a name will lead to the program not being able to compare items as expected by the user.

### Lists saving

Once the program has generated the shopping list, it can be saved as a text file on the user's computer. The user will be prompted for a filename. This file can't be reused in another program run as an inventory or as a "needs" list.

After that, the program will also propose to save inventory and "needs" list on the user's computer anq prompt for a filename. These files can be reused in another program run as inventories or "needs" lists (some rules need to be considered for [encrypted files](#encryption)).

### Encryption

When saving inventories and "needs" lists, the program offers the possibility to encrypt the files using a special key choosed by the user. This will encrypt the names and types of the list printed to the file.

When using an encrypted file created by a previous run of the program as an inventory or as a "need" list, the key used to encrypt the program will be asked to the user. If the user is unable to provide the key, the file will still be imported, but the values won't be decrypted, causing dummy data to be printed.

#### Caution regarding encryption

This project is a learning project and uses the "[Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher)" encryption technique to encrypt data.

This technique isn't secure nowadays to ensure the safety of data. Thus, users are warned that they shouldn't rely on this program's encryption capabilities to store any kind of sensible data.

## Contributing

If you find any issue while using the program or want to contribute, please <a href="https://github.com/NestorNebula/shopping-list/issues">open an issue</a>.

## Acknoledgements

- [GoogleTest](https://github.com/google/googletest)
- [vcpkg](https://vcpkg.io/)

## License

[![MIT License](https://img.shields.io/badge/License-MIT-darkcyan.svg?style=for-the-badge)](https://github.com/NestorNebula/shopping-list/blob/main/LICENSE)

© Noa Houssier - 2025

<p align='right'>(<a href='#top'>go back to the top</a>)</p>
