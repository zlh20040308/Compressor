cd build/
rm -rf *
cmake ..
make
./decompressor ../zipfile ../dest.txt ../key.txt 
cd ..
diff dest.txt cmp.txt
