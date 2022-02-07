all:
	make build
	make run

client:	client.out
	./client.out

build:
	clang++ integrations/server.cpp -Isocket -o server.out
	clang++ integrations/client.cpp -Isocket -o client.out

test:
	clang++ tests/*.test.cpp -Isocket -o test_main.out
	./test_main.out

run:
	./server.out

clean:
	rm -rf *.out client server