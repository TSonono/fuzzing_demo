AFL_CC=afl-gcc
AFL_CXX=afl-g++
initial=`pwd`

afl() {
    if [ -d "build_afl" ]
    then
        cd build_afl
    else
        mkdir build_afl && \
        cd build_afl
    fi
    export AFL_USE_ASAN=1 && \
    cmake \
    -DCMAKE_C_COMPILER=${AFL_CC} \
    -DCMAKE_CXX_COMPILER=${AFL_CXX} \
    -DCMAKE_C_FLAGS="-O9 -std=c99 -Wall -Wextra -Wpedantic -Wshadow -DFUZZ_TOOL=1" ../../ && \
    make
    cd $initial
}

libfuzzer() {
    if [ -d "build_libfuzzer" ]
    then
        cd build_libfuzzer
    else
        mkdir build_libfuzzer && \
        cd build_libfuzzer
    fi
    cmake \
    -DCMAKE_TRY_COMPILE_TARGET_TYPE="STATIC_LIBRARY" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=fuzzer,address" \
    -DCMAKE_C_FLAGS="-std=c99 -Wall -Wextra -Wpedantic -Werror -g -O1 -fsanitize=fuzzer,address -DFUZZ_TOOL=2" \
    -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic -Werror -g -O1 -fsanitize=fuzzer,address -DFUZZ_TOOL=2" ../../ && \
    make
    cd $initial
}

do_afl() {
    afl-fuzz -m none -i input -o output ./build_afl/fuzz_entry
}

do_libfuzzer() {
    ./build_libfuzzer/fuzz_entry output/queue_both
}

reset() {
    rm -rf build_afl && rm -rf build_libfuzzer && rm -rf output
    config;
}

config() {
    cd $initial
    if [ ! -d "output" ]
    then
        mkdir output
        mkdir output/queue_both
        cp -a input/. output/queue_both
    fi
    afl;
    libfuzzer;
}

main_menu() {

    config;
    while true; do
        clear
        read -p "Fuzzing tool

    [1] Americcan Fuzzy Lop
    [2] Libfuzzer
    [3] Reset and rebuild
    [0] Quit

    Select: " yn
        case $yn in
            [1]* ) do_afl;;
            [2]* ) do_libfuzzer;;
            [3]* ) reset;;
            [0]* ) return 0;;
            * ) echo "Invalid";;
        esac

    done
}

main_menu
