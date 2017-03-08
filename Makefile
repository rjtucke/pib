CXX = /home/rtucker/bin/g++
CXXFLAGS = -Wall -Wextra -std=c++0x
BIN = .
OBJ = obj
INCLUDE = include
SRC = src

calc_coeffs : $(OBJ)/calc_coeffs.o
	g++ -o $@ $^

clean : 
	rm -f $(OBJ)/*.o calc_coeffs

$(OBJ)/%.o : $(SRC)/%.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

.PHONY : clean
