CC=gcc
RM=rm -f

CFLAGS=-g
CFLAGS+=-lpthread

TARGET=figure11_2
TARGET+=figure11_3
TARGET+=figure11_4
TARGET+=figure11_5
TARGET+=pthread_equal
TARGET+=pthread_detach

OBJECTS=figure11_10.o
OBJECTS+=figure11_11.o
OBJECTS+=figure11_12.o
OBJECTS+=figure11_13.o
OBJECTS+=figure11_14.o

all: $(TARGET) $(OBJECTS);

figure11_2: figure11_2.c
	$(CC) $^ -o $@ $(CFLAGS) 

figure11_3: figure11_3.c
	$(CC) $^ -o $@ $(CFLAGS) 

figure11_4: figure11_4.c
	$(CC) $^ -o $@ $(CFLAGS) 

figure11_5: figure11_5.c
	$(CC) $^ -o $@ $(CFLAGS) 

figure11_10.o: figure11_10.c
	$(CC) $^ -c -o $@ $(CFLAGS) 

figure11_11.o: figure11_11.c
	$(CC) $^ -c -o $@ $(CFLAGS) 

figure11_12.o: figure11_12.c
	$(CC) $^ -c -o $@ $(CFLAGS) 

figure11_13.o: figure11_13.c
	$(CC) $^ -c -o $@ $(CFLAGS) 

figure11_14.o: figure11_14.c
	$(CC) $^ -c -o $@ $(CFLAGS) 

pthread_detach: pthread_detach.c
	$(CC) $^ -o $@ $(CFLAGS) 

pthread_equal: pthread_equal.c
	$(CC) $^ -o $@ $(CFLAGS) 

clean:
	$(RM) $(TARGET) $(OBJECTS)
