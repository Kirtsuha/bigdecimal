CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

GTEST_DIR = googletest/googletest

CXXFLAGS += -I./googletest/googletest/include -I$(GTEST_DIR)

all: test

test: bigdecimal_tests.o bigdecimal.o gtest_main.o gtest-all.o
	$(CXX) $(CXXFLAGS) -o test $^ -lpthread
	./test

bigdecimal.o: src/bigdecimal.cpp src/bigdecimal.h
	$(CXX) $(CXXFLAGS) -c src/bigdecimal.cpp

bigdecimal_tests.o: src/bigdecimal_tests.cpp src/bigdecimal.h
	$(CXX) $(CXXFLAGS) -c src/bigdecimal_tests.cpp

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_DIR)/src/gtest_main.cc
	$(CXX) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

clean:
	rm -f *.o test

.PHONY: all test clean