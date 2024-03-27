SRC = client.c server.c
OBJ = $(SRC:.c=)

all: $(OBJ)

%: %.c
	gcc -o $@ $<

clean:
	rm -f $(OBJ)
