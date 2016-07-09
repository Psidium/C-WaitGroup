# C-WaitGroup example

This is where the library was born :)

I've searched for a WaitGroup implementation in C and didn't found any, so I deemed it was more easy to write one myself.

The `main` program is supposed to read a file and find the string `VIRUS` on the 500th byte.

Each file is read in a thread of its own.

# Build and run

You'll need `cmake` to run the project:

```bash
mkdir build
cd build
cmake ..
make
./mainOut
```
