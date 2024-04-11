CC = g++
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -std=c++17 -Wall
MAIN = main
MOD1 = double_pendulum
SUB_LIB = include/
SUB_SRC = src/


$(MAIN): $(MAIN).o $(MOD1).o
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).o $(MOD1).o $(LFLAGS)

$(MAIN).o: $(SUB_SRC)$(MAIN).cpp $(SUB_LIB)$(MOD1).h
	$(CC) $(CFLAGS) -c $(SUB_SRC)$(MAIN).cpp $(LFLAGS)

$(MOD1).o: $(SUB_SRC)$(MOD1).cpp $(SUB_LIB)$(MOD1).h
	$(CC) $(CFLAGS) -c $(SUB_SRC)$(MOD1).cpp $(LFLAGS)

clean:
	rm -f $(MAIN).o $(MOD1).o $(MAIN)