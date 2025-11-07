SOURCES		= main.cpp
HEADERS		= MutantStack.hpp
OBJECTS_DIR = .objects/
DEPENDS_DIR	= .deps/
OBJECTS     = ${SOURCES:%.cpp=${OBJECTS_DIR}%.o}
DEPS		= ${SOURCES:%.cpp=${DEPENDS_DIR}%.d}
NAME		= Mutated_abomination
CXX         = c++
CXX_FLAGS   = -Wall -Wextra -Werror -std=c++98
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEPENDS_DIR)$*.d

all: ${NAME}
	@echo "Building done: ${NAME} is ready."

${OBJECTS_DIR}%.o : %.cpp | ${DEPENDS_DIR} ${OBJECTS_DIR}
	@echo "Compiling $< ..."
	@${CXX} ${CXX_FLAGS} ${DEPFLAGS} -c $< -o $@

${NAME}: ${OBJECTS} ${OBJECTS_DIR} ${DEPENDS_DIR} ${HEADERS}
	@${CXX} ${CXX_FLAGS} ${OBJECTS} -o ${NAME}
	@echo "${NAME} has been successfully generated."

${OBJECTS_DIR} ${DEPENDS_DIR}:
	@echo "Creating .objects and .deps folder..."
	@mkdir -p $@

clean:
	@echo "Deleting objects and dependency files..."
	@rm -rf ${OBJECTS_DIR} ${DEPENDS_DIR}
	@echo "Objects and dependency files deleted."

fclean: clean
	@echo "Deleting executables, objects and dependency files..."
	@rm -f ${NAME}
	@echo "Executables, objects and dependency files deleted."

re: fclean all
	@echo "🔄"

-include ${DEPS}

.PHONY: all clean fclean re
