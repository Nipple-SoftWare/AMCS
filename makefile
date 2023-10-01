CC = g++
FLAGS =

OUT = army
IN = *.cpp
SRC = *.cpp *.hpp

$(OUT): $(IN)
	$(CC) -o $@ $^ $(FLAGS)
