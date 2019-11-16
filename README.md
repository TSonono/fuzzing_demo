# Fuzz demo

This project is a simple demonstration of fuzz testing using American Fuzzy loop (AFL) and LLVM Clang's libfuzzer. It parses a [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol) packet and tries to read the last byte in the data field of the packet.

## Requirements
- [AFL](http://lcamtuf.coredump.cx/afl/)
- [Clang](https://llvm.org/docs/LibFuzzer.html)
- CMake
- Linux (macOS not tested)

Or you can use the provided `Dockerfile` in the `/fuzz-docker` directory.

## Build
To make things easier, a bash script is provided in the `/fuzz` directory which builds the project both for AFL and libfuzzer with CMake. 

```bash
cd fuzz
./fuzz.sh
```
If the shell script needs permissions to run, `chmod +x ./fuzz.sh` should make it able to run.

## Run
If you are using the shell script provided. It is as simple as selecting the fuzzer in menu screen of the script. 

## The script
This demo is setup in a way to demonstrate the abilities of fuzz testing. I encourage you to take a look at the bash script and `fuzz/test.c` if you want to learn how to build/compile a project for fuzzing.

## Todos
- Coverage data
- Multiple core configuration
- Other performance enhancements

## Bugs
- Sometimes the afl fuzzer is not able to read data correctly (the status screen shows that no new paths have been found). Running the reset option in the script solves this.