INSTALL_BIN = scream
INSTALL_DIR = /usr/local/bin

CC     = gcc
CFLAGS = -I./include
C_OBJS = $(wildcard */*.c)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

install: $(BIN)
	mv $(BIN) $(INSTALL_DIR)/$(BIN)

clean:
	rm $(C_OBJS) && \
	rm $(INSTALL_BIN)
