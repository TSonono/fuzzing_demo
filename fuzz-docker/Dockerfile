FROM ubuntu:18.04
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y clang clang-tools git gcc g++ gcc-multilib sudo wget nano build-essential cmake libsodium-dev libcmocka-dev cppcheck lcov screen gdb python3 python3-pip curl
RUN apt-get clean && apt-get autoremove -y 

# WORKDIR /tmp
# RUN curl -SL http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
# 	| tar -xJC . && \
# 	mv clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_9.0.0 && \
# 	echo 'export PATH=/clang_9.0.0/bin:$PATH' >> ~/.bashrc && \
# 	echo 'export LD_LIBRARY_PATH=/clang_9.0.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc

WORKDIR /tmp
RUN wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
RUN tar -xvf afl-latest.tgz
RUN rm afl-latest.tgz && mv afl-* afl-latest
WORKDIR /tmp/afl-latest/llvm_mode
RUN sed -i "s/-fno-rtti/-Wl,-znodelete -fno-rtti/g" Makefile
WORKDIR /tmp/afl-latest
RUN make && make -C llvm_mode LLVM_CONFIG=llvm-config-6.0 CC=clang CXX=clang++
RUN make install \
	&& cd .. \
	&& rm -rf afl-latest*

WORKDIR /tmp
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.15.0.tar.bz2 \
	&& tar xvf valgrind-3.15.0.tar.bz2 \
	&& cd valgrind-3.15.0 \
	&& ./configure \
	&& make \
	&& make install \
	&& cd .. \
    && rm -rf valgrind*

# WORKDIR /tmp
# RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.4/cmake-3.15.4.tar.gz \
# 	&& tar xvf cmake-3.15.4.tar.gz \
# 	&& cd cmake-3.15.4 \
#     && ./bootstrap \
#     && make \
#     && make install \
#     && cd .. \
#     && rm -rf cmake*


# WORKDIR /tmp
# RUN wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz \
# 	&& tar -xvf afl-latest.tgz \
# 	&& rm afl-latest.tgz && mv afl-* afl-latest \
# 	&& cd /tmp/afl-latest/llvm_mode \
# 	&& sed -i "s/-fno-rtti/-Wl,-znodelete -fno-rtti/g" Makefile \
# 	&& cd /tmp/afl-latest \
# 	&& make && make -C llvm_mode LLVM_CONFIG=llvm-config CC=clang CXX=clang++


WORKDIR /
# Start from a Bash prompt
CMD [ "/bin/bash" ]
