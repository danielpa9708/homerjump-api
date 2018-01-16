BIN = game.lib
OBJ = obj/api.o obj/animation.o obj/sprite.o
LIB =
INC = include

MGW = c:/MinGW/x86_64-w64-mingw32
MGWI = $(MGW)/include
MGWL = $(MGW)/lib

CFLAGS = -iquote$(INC)

GCC = g++
AR  = ar
RM  = rm -f -v
CP  = cp -v
MKDIR = mkdir


compile: $(BIN)

clear:
	$(RM) $(BIN) $(OBJ)

$(BIN): $(OBJ)
	$(AR) r $(BIN) $(OBJ)

obj/%.o: src/%.cpp
	$(GCC) -c -o obj/$*.o src/$*.cpp $(CFLAGS)
