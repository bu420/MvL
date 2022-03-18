g++ -g -std=c++20 ^
-Isrc/client -Isrc/common -Iinc -Llib ^
-o client ^
src/client/*.cpp src/common/*.cpp ^
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lenet64 -lws2_32 -lwinmm