all:
	make build
	make test

build:
	clang++ tests/server.cpp -o server.out
	clang++ tests/client.cpp -o client.out

test:
	./server.out

clean:
	rm -rf *.out client server