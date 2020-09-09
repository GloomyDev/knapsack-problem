CXX=g++

STDFLAGS = -std=c++17 -Wall -Weverything -pedantic

RM=rm -f

BINARIES = back brute dynamic generator

all: $(BINARIES)

back: back.o
	$(CXX) $(STDFLAGS) $^ -o back

brute: brute.o
	$(CXX) $(STDFLAGS) $^ -o brute

dynamic: dynamic.o
	$(CXX) $(STDFLAGS) $^ -o dynamic

generator: generator.o
	$(CXX) $(STDFLAGS) $^ -o generator

%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<

clean:
	$(RM) *.o
	$(RM) $(BINARIES)
