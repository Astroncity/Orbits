gcc -c -g main.c -o util/main.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/image.c -o util/image.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/gui.c -o util/gui.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/utils.c -o util/utils.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/bullet.c -o util/bullet.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/core.c -o util/core.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/enemies/enemyBasic.c -o util/enemyBasic.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/player.c -o util/player.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/snipertower.c -o util/snipertower.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/font.c -o util/font.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/particleSystem.c -o util/particleSystem.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/enemies/enemySplitter.c -o util/enemySplitter.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
gcc -c -g include/enemies/enemyShield.c -o util/enemyShield.o -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread




gcc -g util/main.o util/image.o util/gui.o util/utils.o util/bullet.o util/core.o util/enemyBasic.o util/player.o util/snipertower.o util/font.o util/particleSystem.o util/enemySplitter.o util/enemyShield.o testres.rc.data -o "build/main.exe" -Wall -O3 -std=c99 -Wno-missing-braces -Wno-maybe-uninitialized -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
#cd ..
#cloc raylib_test --skip-win-hidden --exclude-dir=lib,raylib.h,rlgl.h,image.c,.vscode,testres.rc,testres.rc.data,run.ps1,font.c
#cd raylib_test