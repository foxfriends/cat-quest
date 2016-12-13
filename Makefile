CXX = g++-5
CXXFLAGS = -std=c++14 -MMD -Wall $(shell sdl2-config --cflags --libs)
SOURCES = $(shell find cat_quest -name *.cpp)
OBJECTS = ${SOURCES:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = catquest
${EXEC}: ${OBJECTS}
	@echo Linking executable
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} -lSDL2_ttf -lSDL2_image -lSDL2_mixer
	@echo Done!
.PHONY: clean clean-dep list test
clean:
	-@rm ${OBJECTS} ${DEPENDS} ${EXEC} 2> /dev/null || true
clean-dep:
	-@rm ${OBJECTS} ${DEPENDS} 2> /dev/null || true
list:
	@echo ${OBJECTS}
