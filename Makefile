TARGETS = insertionsort.o \
		mergesort.o \
		quicksort.o \
		timealgorithms.o \
		timealgorithms \
		consistentresultverification \
		sortedverification \
		createdata
obj = *.o

all: $(TARGETS)

insertionsort.o: insertionsort.cpp
	g++ $^ -g -c 

mergesort.o: mergesort.cpp
	g++ $^ -g -c 

quicksort.o: quicksort.cpp
	g++ $^ -g -c 
	
timealgorithms.o: timealgorithms.cxx 
	g++ $^ -g -c 

timealgorithms: timealgorithms.o insertionsort.o mergesort.o quicksort.o
	g++ $^ -g -o $@ 

consistentresultverification: consistentresultverification.cxx
	g++ $^ -g -o $@

sortedverification: sortedverification.cxx
	g++ $^ -g -o $@
	
createdata: createdata.cxx
	g++ $^ -g -o $@

clean:
	rm -f $(obj)