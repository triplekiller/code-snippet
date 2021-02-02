objects = shared_mutex.o shm_test.o

LDFLAGS += -lpthread -lrt

shm_test: $(objects)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm *.o shm_test

*.o: *.c
	$(CC) -o $@ -c $<
