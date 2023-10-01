RootDir = ../

C = g++
Libs = 
Flags = -Wl,-rpath,'$$ORIGIN' -I$(RootDir)/inc/ -L$(RootDir)/bin/

ObjDir = $(RootDir)/obj
ObjFiles = $(ObjDir)/AMCS.o

Binary = $(RootDir)/bin/AMCS

$(Binary): $(ObjFiles)
	$(C) $(Flags) $^ -o $@ $(Libs)

$(ObjDir)/%.o: %.cpp
	$(C) -c $(Flags) $< -o $@
