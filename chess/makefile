CXX=g++
CXXFLAGS=-std=c++14 -Wall -pedantic -Wextra -Wno-sign-compare -MMD
EXEC=chess

DIRS=. model model/pieces view controller

CCFILES=$(wildcard $(addsuffix /*.cc, $(DIRS)))

OBJECTS=$(CCFILES:.cc=.o)
DEPENDS=$(CCFILES:.cc=.d)

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f ${EXEC} ${OBJECTS} ${DEPENDS}
