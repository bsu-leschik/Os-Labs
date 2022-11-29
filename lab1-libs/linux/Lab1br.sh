mkdir script

printf "*creating number object file...\n"
g++ -c -o script/number.o Number/Number.cpp
printf "*archiving libnumber.a...\n"
ar rcs script/libnumber.a script/number.o
printf "*built libnumber.a\n"

printf "*creating and linking vector object file...\n"
g++ -c -fpic -o script/vector.o Vector/Vector.cpp -B static -lnumber
printf "*creating libvector.so...\n"
g++ -shared -o script/libvector.so script/vector.o
printf "*built libvector.so\n"

printf "*adding libvector.so path..\n"
export LD_LIBRARY_PATH="script"
printf "*building project...\n"
g++ -o script/a.out main.cpp -B dynamic -L script -lvector  -B static -L script -lnumber
printf "*built project\n"

printf "*running...\n"
./script/a.out

printf "*cleaning up...\n"
export LD_LIBRARY_PATH=""
rm -rf script
