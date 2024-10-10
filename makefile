# directories
BIN        = bin
SRC        = .

# files
LIBCPP      = $(shell find $(SRC) -name '*.cpp')
LIBOBJ      = $(LIBCPP:%.cpp=%.o)

# compile & link flages
CFLAGS     = -std=c++11 -Wall -fPIC -g
LIBFLAGS   = -shared
TARGET     = libdbstorage.so
INSTALL    = /usr/local

all: library

library: $(TARGET)

$(TARGET): $(LIBOBJ)
	$(CXX) $(LIBFLAGS) -o $(TARGET) $(LIBOBJ)


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -rf $(BIN)
	find $(SRC) -type f -name '*.o' -delete

install:
	cp $(TARGET) $(INSTALL)/lib/$(TARGET)

format:
	astyle --options=astyle.options $(ALLLIB)
	astyle --options=astyle.options $(ALLTEST)
