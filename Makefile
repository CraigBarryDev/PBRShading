CC:=g++
LIBS:=-lm -lGL -lGLU -lglut ./framework/libSOIL.a
BIN:=app
FLAGS:=-std=c++11

OBJECTS:= backdrop.o cannon.o collisions.o cylinder.o framework/camera.o framework/EntityRenderer.o framework/frameTimer.o framework/glGraphics.o framework/keyboard.o framework/loader.o framework/model/Entity.o framework/model/ModelTexture.o framework/model/RawModel.o framework/model/TexturedModel.o framework/mouse.o framework/shaders.o framework/shaders/backdropShader.o framework/shaders/ParticleShader.o framework/shaders/StaticShader.o init.o inputHandler.o main.o nSidedPolygon.o particles.o peg.o sphere.o

all: $(BIN)
	./$(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(FLAGS) -o $(BIN) $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

remake:
	make clean
	make all

clean:
	rm -f $(OBJECTS) $(BIN)