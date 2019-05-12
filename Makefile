BIN := bin
SRC_DIR := src
TEST_DIR := tests
SRC_BIN := bin/obj
TEST_BIN := bin/tests
SRC_FILES := $(shell find $(SRC_DIR)/ -type f -name *.cpp)
TEST_FILES := $(shell find $(TEST_DIR)/ -type f -name *.cpp)
SRC_TARGET := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_BIN)/%.o,$(SRC_FILES))
TEST_TARGET := $(patsubst $(TEST_DIR)/%.cpp,$(TEST_BIN)/%.o,$(TEST_FILES))
CATCH_TARGET := $(filter-out $(SRC_BIN)/main.o, $(SRC_TARGET)) $(TEST_TARGET)

CXX := g++
LIBS := -lcrypto -lboost_system -lboost_filesystem
FLAGS := -g

$(SRC_BIN)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(FLAGS) -o $@ $<

$(TEST_BIN)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(FLAGS) -o $@ $<

clean:
	rm -r -f $(BIN)

build-test: $(CATCH_TARGET)
	g++ $(FLAGS) -o "dla-test.exe" $^ $(LIBS)

build-release: $(SRC_TARGET)
	g++ $(FLAGS) -o "dla.exe" $^ $(LIBS)

run-test: build-test
	./dla-test.exe

gen-report: clean build-test
	mkdir -p test-results test-results/catch
	rm -f test-results/catch/results.xml
	./dla-test.exe -r junit >> test-results/catch/results.xml