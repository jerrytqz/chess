CXX=g++
CXXFLAGS=-std=c++14 -Wall -pedantic -Wextra -Wno-sign-compare -MMD
EXEC=chess

# Specify the directories containing source files
DIRS=. model view controller

# Find all .cc files in the specified directories
CCFILES=$(wildcard $(addsuffix /*.cc, $(DIRS)))

# Derive object and dependency file names
OBJECTS=$(CCFILES:.cc=.o)
DEPENDS=$(CCFILES:.cc=.d)

# Linking the executable
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

# Include the dependencies
-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f ${EXEC} ${OBJECTS} ${DEPENDS}
