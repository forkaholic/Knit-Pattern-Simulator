make: main.cpp
	g++ -o out main.cpp -I../libgraphics/include -L../libgraphics/lib -I./include -L./lib -lgraphics -lglew32 -lopengl32 -lfreeglut

