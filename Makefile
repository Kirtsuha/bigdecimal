CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Путь к локальному Google Test
GTEST_DIR = googletest/googletest

# Цели сборки
all: test

# Сборка и запуск тестов
test: bigdecimal_tests.o bigdecimal.o gtest_main.o gtest-all.o
	$(CXX) $(CXXFLAGS) -o test bigdecimal_tests.o bigdecimal.o gtest_main.o gtest-all.o -lpthread
	./test  # Автоматический запуск тестов

# Компиляция объектных файлов
bigdecimal.o: src/bigdecimal.cpp src/bigdecimal.h
	$(CXX) $(CXXFLAGS) -c src/bigdecimal.cpp

bigdecimal_tests.o: src/bigdecimal_tests.cpp src/bigdecimal.h
	$(CXX) $(CXXFLAGS) -I./googletest/googletest/include -I$(GTEST_DIR) -c src/bigdecimal_tests.cpp

# Явное указание путей к gtest файлам
gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -I./googletest/googletest/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_DIR)/src/gtest_main.cc
	$(CXX) $(CXXFLAGS) -I./googletest/googletest/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc

# Очистка временных файлов
clean:
	rm -f *.o test

# Правило по умолчанию
.PHONY: all test clean