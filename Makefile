CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Путь к локальному Google Test
GTEST_DIR = googletest/googletest

# Флаги для включения заголовочных файлов Google Test
CXXFLAGS += -I./googletest/googletest/include -I$(GTEST_DIR)

# Цели сборки
all: test

# Сборка тестов
test: bigdecimal_tests.o bigdecimal.o gtest_main.o gtest-all.o
	@echo "Linking test executable..."
	$(CXX) $(CXXFLAGS) -o test $^ -lpthread
	./test

# Компиляция объектных файлов
bigdecimal.o: src/bigdecimal.cpp src/bigdecimal.h
	@echo "Compiling bigdecimal.cpp..."
	$(CXX) $(CXXFLAGS) -c src/bigdecimal.cpp

bigdecimal_tests.o: src/bigdecimal_tests.cpp src/bigdecimal.h
	@echo "Compiling bigdecimal_tests.cpp..."
	$(CXX) $(CXXFLAGS) -c src/bigdecimal_tests.cpp

# Явное указание путей к gtest файлам
gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	@echo "Compiling gtest-all.cc..."
	$(CXX) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_DIR)/src/gtest_main.cc
	@echo "Compiling gtest_main.cc..."
	$(CXX) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

# Очистка временных файлов
clean:
	@echo "Cleaning up..."
	rm -f *.o test

# Правило по умолчанию
.PHONY: all test clean