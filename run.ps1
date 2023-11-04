gcc -c -g main.c -o main.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
gcc -c -g include/utils.c -o utils.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm




gcc -g main.o utils.o -o "build/main.exe" -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

cd build
./main.exe
cd ..

#cd ..
#cloc raylib_test --skip-win-hidden --exclude-dir=lib,raylib.h,rlgl.h,image.c,.vscode,testres.rc,testres.rc.data,run.ps1,font.c
#cd raylib_test