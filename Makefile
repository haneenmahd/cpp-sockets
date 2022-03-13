all:
	make build
	make run

client:	client.out
	./client.out

build:
	clang++ dev/server.cpp -Iinclude -o server.out
	clang++ dev/client.cpp -Iinclude -o client.out

test:
	clang++ tests/*.test.cpp -Iinclude -Itests -o tests_main.out
	./tests_main.out

run:
	./server.out

clean:
	rm -rf *.out client server *.o