CXX=g++
STDFLAGS = -std=c++11 -Wall -Werror
RM=rm -f
BINARIES = back brute dynamic

all: $(BINARIES)
back: back.o
	$(CXX) $(STDFLAGS) $^ -o back
brute: brute.o
	$(CXX) $(STDFLAGS) $^ -o brute
dynamic: dynamic.o
	$(CXX) $(STDFLAGS) $^ -o dynamic
%.o: %.cpp
	$(CXX) $(STDFLAGS) -c $<
clean:
	$(RM) *.o
	$(RM) $(BINARIES)