SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(shell find $(SRC_DIR)/ -type f -name *.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIBS := -lcrypto

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ -c -g -o $@ $<

clean:
	rm -r $(OBJ_DIR)

build-test: $(OBJ_FILES)
	g++ -g -o "dla-test.exe" $^ $(LIBS)

run-test:
	./dla-test.exe

gen-report: clean build-test
	./dla-test.exe -r junit >> report.xml