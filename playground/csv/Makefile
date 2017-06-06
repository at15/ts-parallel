serial.bin: serial.cpp
	@g++ -o serial.bin serial.cpp
	@./serial.bin

.PHONY: py
py: serial.py
	@python serial.py

.PHONY: clean
clean:
	@rm -f a.out serial	