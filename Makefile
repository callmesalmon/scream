OBJS   = $(wildcard */*.c)
CC     = gcc
BIN    = scream

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

install: $(BIN)
	mv $(BIN) /usr/local/bin/$(BIN)

clean:
	rm $(OBJS) && \
	rm $(BIN)
