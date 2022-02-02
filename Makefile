all:
	make build
	make test

client:	client.out
	./client.out

build:
	clang++ tests/server.cpp -Isocket -o server.out
	clang++ tests/client.cpp -Isocket -o client.out

test:
	./server.out

clean:
	rm -rf *.out client server