CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET_DIR = bin
TARGET = $(TARGET_DIR)/autocompletar

SOURCES = main.cpp Termo.cpp Autocompletar.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp Termo.h Autocompletar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Termo.o: Termo.cpp Termo.h

clean:
	rm -f $(OBJECTS)
	rm -rf $(TARGET_DIR)
	