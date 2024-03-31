OUTDIR := .out/
TARGET := client server
CC := gcc
CFLAGS := ltirpc

$(shell mkdir -p $(OUTDIR))

all: $(TARGET) move

header: filetransfer.x
	rpcgen -C filetransfer.x

client: client.o filetransfer_clnt.o filetransfer_xdr.o
	$(CC) -g -o $@ $^ -$(CFLAGS)

server: server.o filetransfer_svc.o filetransfer_xdr.o
	$(CC) -g -o $@ $^ -$(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf client server $(OUTDIR)

move:
	mv *.o $(OUTDIR)
