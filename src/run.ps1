gcc -c -g main.c -o build/main.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -ggdb -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
gcc -c -g include/utils.c -o build/utils.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -ggdb -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm




gcc -g build/main.o build/utils.o -o "build/main.exe" -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -ggdb -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

cd build
./main.exe
cd ..

#cd ..
#cloc name --skip-win-hidden --exclude-dir=lib
#cd name

#cloc Orbits --skip-win-hidden --exclude-dir=lib,raylib.h,rlgl.h,.vscode,run.ps1        