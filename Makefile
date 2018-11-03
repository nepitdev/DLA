SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(shell find $(SRC_DIR)/ -type f -name *.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIBS := -lcrypto

dla: $(OBJ_FILES)
	g++ -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ -c -o $@ $<

clean: dla
	rm -r $(OBJ_DIR)
	$(MAKE) dla