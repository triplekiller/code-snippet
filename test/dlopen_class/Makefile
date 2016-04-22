CXX := g++
SHARED_LIB := triangle.so
TARGET_BIN := dl_test

SHARED_SRC := triangle.cpp
TARGET_SRC := dlopen_class.cpp

LDFLAGS += -ldl

all: $(SHARED_LIB) $(TARGET_BIN)

$(SHARED_LIB): $(SHARED_SRC)
	$(CXX) -fPIC -shared -o $@ $^

$(TARGET_BIN): $(TARGET_SRC)
	$(CXX) -rdynamic -o $@ $^ $(LDFLAGS)

clean:
	-rm -f $(SHARED_LIB) $(TARGET_BIN)
