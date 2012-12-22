gcc -std=c99 test_main.c test_file.c ../src/Filelib.c ../src/Filelib_util.c -I ../src -o file_test
./file_test
