SRC = client.c server.c
OBJ = $(SRC:.c=)
OUTDIR = .output
TERM = kitty

all: $(OBJ)

run: all
	$(TERM) "./server" & disown
	$(TERM) "./client" & disown 

%: %.c
	gcc -o $@ $<

clean:
	rm -f $(OBJ)
