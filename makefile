SRC = src/main.cpp
INCL_DIRS = -I../libgraphics/include -I../libutil/include -Iinclude
LIB_DIRS = -L../libgraphics/lib -L../libutil/lib -Llib
LIBS = -lgraphics -lutil -lglew32 -lopengl32 -lfreeglut


make: 
	g++ -o out.exe $(SRC) $(INCL_DIRS) $(LIB_DIRS) $(LIBS)
	@.\out.exe
