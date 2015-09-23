CC=gcc
MKDIR=mkdir -p
RM=rm -f
SRC_DIR=src
TESTS_DIR=tests
INCLUDE_DIR=include
BUILD_DIR=build

CFLAGS=-Wall -I$(INCLUDE_DIR)

test: CFLAGS += -DDEBUG


SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(BUILD_DIR)/*

test: $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_rcstr $(OBJS) tests/test_rcstr.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_chain $(OBJS) tests/test_chain.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_hashtable $(OBJS) tests/test_hashtable.c
	./run_tests
