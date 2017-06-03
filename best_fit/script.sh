gcc exemple.c -o exemple
gcc -shared -fPIC malloc.c -o malloc.so
export LD_REALOAD=/$PWD/malloc.so
./exemple
