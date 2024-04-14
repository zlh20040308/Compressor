cd build/
rm -rf *
cmake ..
make
./compressor  ../input.txt ../zipfile
