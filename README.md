# zpipe_cpp
A C++ implementation of the `zpipe.c` example from the zlib library, demonstrating how to compress and decompress files using the zlib library.

## Prerequisites
Ensure that you have the following software installed on your machine:

- `zlib` library
- `gcc` (GNU Compiler Collection)

## Building the Application
To compile the application, use the following command:

```bash
g++ zpipe.cpp -o zpipe -lz
```
This command will create an executable file named `zpipe`.

## Running the Application
Once the binary is generated, you can run the application with:

```bash
./zpipe
```

## Input and Output
When executed, the program performs the following operations:

1. Reads the contents of a file named `input.txt`.
2. Compresses the content using the zlib compression algorithm.
3. Writes the compressed data to a file named `output.txt`.

Ensure that an `input.txt` file is present in the same directory as the executable before running the program.

## Example Usage
1. Create an `input.txt` file with the content you wish to compress.
2. Run the program:
```bash
./zpipe
```
3. After execution, the compressed output will be stored in `output.txt`.

## Troubleshooting
- Missing zlib: If you encounter errors about missing zlib, ensure that zlib is installed and properly linked. On many Linux distributions, you can install zlib with a package manager, for example:

```bash
sudo apt-get install zlib1g-dev
```
- Compilation Errors: Ensure that your `gcc` and `zlib` library paths are correctly set up. If you're using a different compiler or have zlib installed in a non-standard location, you may need to adjust the compilation command accordingly.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue to discuss improvements or bugs.

## Acknowledgements
This project is based on the zpipe.c example from the zlib library, showcasing the practical use of zlib for file compression and decompression in C++.

## Contact
For any questions or feedback, feel free to open an issue on the GitHub repository or contact the project maintainers.