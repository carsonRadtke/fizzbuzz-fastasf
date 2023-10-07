FROM ubuntu

RUN apt update && apt upgrade -y
RUN apt install -y clang make pv
RUN apt install -y gdb valgrind strace

