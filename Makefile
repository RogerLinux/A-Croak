CC = g++
CFLAG = -O -Wall
SRC = ./src
INCLUDE = ./include

DIR = ./bin

##Training executable file
AC = A-Croak
##Word vector similarity executable file
SL = similarity

TARGET1 = $(DIR)/$(AC)
TARGET2 = $(DIR)/$(SL)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC)/$(AC).cpp
	$(CC) $(CFLAG) -I$(INCLUDE) -I$(SRC) $^ -o $@

$(TARGET2): $(SRC)/$(SL).cpp
	$(CC) $(CFLAG) -I$(INCLUDE) -I$(SRC) $^ -o $@
clean:
	rm -f $(DIR)/*
