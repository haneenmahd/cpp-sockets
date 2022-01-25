all:
	make build
	make test

build:
	clang++ server.cpp -o server.out
	clang++ client.cpp -o client.out

test:
	./server.out

clean:
	rm -rf *.out client server