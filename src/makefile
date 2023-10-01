RootDir = ../../

C = x86_64-w64-mingw32-gcc
Libs = 
Flags = -Wl,-rpath,'$$ORIGIN' -I$(RootDir)/inc/ -L$(RootDir)/bin/

ObjDir = $(RootDir)/obj/game
ObjFiles = $(ObjDir)/main.o

Binary = $(RootDir)/bin/game.exe

$(Binary): $(ObjFiles)
	$(C) $(Flags) $^ -o $@ $(Libs)

$(ObjDir)/%.o: %.c
	$(C) -c $(Flags) $< -o $@
