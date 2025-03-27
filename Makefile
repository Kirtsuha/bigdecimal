CXX = g++
CXXFLAGS = -std=c++20 -Wall -O3
SRCDIR = src
TESTDIR = tests
BINDIR = bin

all: $(BINDIR)/pi

$(BINDIR)/pi: $(SRCDIR)/main.o $(SRCDIR)/bigdecimal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TESTDIR)/bigdecimal_tests: $(TESTDIR)/bigdecimal_tests.o $(SRCDIR)/bigdecimal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
test: $(TESTDIR)/bigdecimal_tests
	$(TESTDIR)/bigdecimal_tests

clean:
	rm -f $(SRCDIR)/*.o $(TESTDIR)/*.o $(BINDIR)/pi $(TESTDIR)/bigdecimal_tests