# Target to remove all non-.c and non-.h files
clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "Makefile" -exec rm -f {} +

.PHONY: clean
