CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
PKGFLAGS = $(shell pkg-config --cflags --libs raylib)
SRC = tesseract.cpp
OUT = tesseract

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(PKGFLAGS)

clean:
	rm -f $(OUT)
