CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = bank
SRCS = main.cpp Account.cpp Customer.cpp Transaction.cpp Bank.cpp Admin.cpp Authentication.cpp FileManager.cpp Validation.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) data/accounts.dat data/transactions.dat
