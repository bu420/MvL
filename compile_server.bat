g++ -g -std=c++20 ^
-Isrc/server -Isrc/common -Iinc -Llib ^
-o server ^
src/server/*.cpp src/common/*.cpp ^
-lmingw32 -lSDL2main -lSDL2 -lenet64 -lws2_32 -lwinmm