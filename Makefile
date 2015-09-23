SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

CFLAGS=-Wall -I$(INCLUDE_DIR)

.PHONY: libs

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/*

test: $(OBJS)
	gcc $(CFLAGS) -o $(BUILD_DIR)/test_rcstr tests/test_rcstr.c

