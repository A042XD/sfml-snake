g++ -std=c++23 -Iinclude main.cpp -c main.o
g++ -std=c++23 main.o -L"./lib" -lsfml-graphics -lsfml-window -lsfml-system -o main.exe
main.exe
PAUSE
