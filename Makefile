SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(shell find $(SRC_DIR)/ -type f -name *.cpp)
OBJ_FILES := $(filter-out obj/source/main.o, $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)))

REL_DIR := src/source
BIN_DIR := obj/source
REL_FILES := $(shell find $(REL_DIR)/ -type f -name *.cpp)
BIN_FILES := $(patsubst $(REL_DIR)/%.cpp,$(BIN_DIR)/%.o,$(REL_FILES))

LIBS := -lcrypto -lboost_system -lboost_filesystem
FLAGS := -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ -c $(FLAGS) -o $@ $< -I /usr/share/include/

clean:
	rm -r -f $(OBJ_DIR)

build-test: $(OBJ_FILES)
	g++ $(FLAGS) -o "dla-test.exe" $^ $(LIBS) -L/usr/share/lib/

build-release: $(BIN_FILES)
	g++ $(FLAGS) -o "dla.exe" $^ $(LIBS) -L/usr/share/lib/

run-test:
	./dla-test.exe

gen-report: clean build-test
	mkdir -p test-results test-results/catch
	rm -f test-results/catch/results.xml
	./dla-test.exe -r junit >> test-results/catch/results.xml