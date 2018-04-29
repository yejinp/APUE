CC=gcc
RM=rm -f

CFLAG=-g

TARGET=figure4_3
TARGET+=figure4_8
TARGET+=figure4_9
TARGET+=set_user_id

OBJECT=

all: $(TARGET) $(OBJECT);

figure4_3:figure4_3.c
	$(CC) $^ -o $@

figure4_8:figure4_8.c
	$(CC) $^ -o $@

figure4_9:figure4_9.c
	$(CC) $^ -o $@

set_user_id:set_user_id.c
	$(CC) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECT)
