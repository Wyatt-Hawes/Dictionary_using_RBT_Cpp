CC = g++ -g
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Wpedantic -g -Ofast#$(shell pkg-config --cflags)

all: DictionaryTest DictionaryTest WordFrequency

Order: Dictionary.o Order.o
	$(CC) $(CFLAGS) -o  $@ $^ 


DictionaryTest: Dictionary.o DictionaryTest.o
	$(CC) $(CFLAGS) -o  $@ $^ 

WordFrequency: Dictionary.o WordFrequency.o
	$(CC) $(CFLAGS) -o  $@ $^ 

DictionaryTest1: Dictionary.o DictionaryTest1.o
	$(CC) $(CFLAGS) -o  $@ $^ 


%.o: %.c
	$(CC) $(CFLAGS) -c -Ofast 

clean:
	rm -f *.o
	rm -f DictionaryTest
	rm -f Order

