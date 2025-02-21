CXX = g++
CXXFLAGS = -Wall -Werror -I src -I gtest -O0

all: main student_gtests

src/bst.o: src/bst.cpp src/bst.h
	$(CXX) $(CXXFLAGS) -c src/bst.cpp -o src/bst.o

src/bstree.o: src/bstree.cpp src/bstree.h src/bst.h
	$(CXX) $(CXXFLAGS) -c src/bstree.cpp -o src/bstree.o

src/avltree.o: src/avltree.cpp src/avltree.h src/bst.h
	$(CXX) $(CXXFLAGS) -c src/avltree.cpp -o src/avltree.o

src/main.o: src/main.cpp src/bst.h src/bstree.h src/avltree.h src/timer.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

main: src/main.o src/bst.o src/bstree.o src/avltree.o
	$(CXX) $(CXXFLAGS) src/main.o src/bst.o src/bstree.o src/avltree.o -o main

gtest/student_gtests.o: gtest/student_gtests.cpp
	$(CXX) $(CXXFLAGS) -c gtest/student_gtests.cpp -o gtest/student_gtests.o

student_gtests: gtest/student_gtests.o src/bst.o src/bstree.o src/avltree.o
	$(CXX) $(CXXFLAGS) gtest/student_gtests.o src/bst.o src/bstree.o src/avltree.o \
		-lgtest -lgtest_main -lpthread -o student_gtests

clean:
	rm -f src/*.o gtest/*.o main student_gtests
