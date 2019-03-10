SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(shell find $(SRC_DIR)/ -type f -name *.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIBS := -lcrypto

dla: $(OBJ_FILES)
	g++ -o "dla.exe" $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ -c -g -o $@ $<

clean:
	rm -r $(OBJ_DIR)
	$(MAKE) dla

cleanTest:
	rm -r $(OBJ_DIR)
	$(MAKE) buildTest

buildTest: $(OBJ_FILES)
	g++ -g -o "catch-dla.exe" $^ $(LIBS)
	$(MAKE) runTest

runTest:
	./catch-dla.exe

test:
	$(MAKE) cleanTest