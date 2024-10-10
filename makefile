INCLUDE_DIR=../sql-parser/src
LIB_DIR=/lib/x86_64-linux-gnu

OBJS =  dbblock.o dbfile.o

#all: $(OBJS)

dbstorage.so: $(OBJS)
	g++ -L$(LIB_DIR) $(OBJS) -o $@

# General rule for compilation
%.o: %.cpp *.h
	g++ -I$(INCLUDE_DIR) -std=c++11 -std=c++0x -Wall -Wno-c++11-compat -DHAVE_CXX_STDHEADERS -D_GNU_SOURCE -D_REENTRANT -O3 -c -ggdb -o "$@" "$<" 

clean:
	rm -f dbstorage.so *.o
