CXX = g++
CXXFLAGS = -std=c++23 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++23 -Ih -pthread
OBJECTS = ./obj/aphw1.o ./obj/main.o ./obj/aphw1_unittest.o
# OBJECTS = aphw1.o main.o aphw1_unittest.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/aphw1.o: ./cpp/aphw1.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw1.cpp -o ./obj/aphw1.o
./obj/aphw1_unittest.o: ./cpp/aphw1_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw1_unittest.cpp -o ./obj/aphw1_unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
aphw1.o: aphw1.cpp
	$(CXX) $(CXXFLAGS) aphw1.cpp -o aphw1.o
aphw1_unittest.o: aphw1_unittest.cpp
	$(CXX) $(CXXFLAGS) aphw1_unittest.cpp -o aphw1_unittest.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.o
clean:
	 rm -fv $(TARGET) $(OBJECTS)

# CXX = g++
# CXXFLAGS = -std=c++23 -Wall -c
# LXXFLAGS = -std=c++23
# OBJECTS = main.o aphw1.o aphw1_unittest.o
# TARGET = main


# $(TARGET): $(OBJECTS)
# 	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET) -lgtest -lgtest_main -pthread
# main.o: main.cpp aphw1_unittest.cpp
# 	$(CXX) $(CXXFLAGS) main.cpp
# aphw1.o:aphw1.cpp aphw1.h
# 	$(CXX) $(CXXFLAGS) aphw1.cpp
# aphw1_unittest.o: aphw1_unittest.cpp
# 	$(CXX) $(CXXFLAGS) aphw1_unittest.cpp
# clean:
# 	rm -f $(TARGET) $(OBJECTS)

