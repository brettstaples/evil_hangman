CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o generic_vector.o
OBJECTS_TEST = my_string.o unit_test.o test_def.o
ALL_OBJECTS = main.o my_string.o unit_test.o test_def2.o my_string.o generic_vector.o
SRC_TEST = unit_test.c
SRC = main.c
IMPL = my_string.c
IMPL_TEST = test_defs.c
GEN_IMPL = generic_vector.c
EXE = string_driver
EXE_TEST = unit_test

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS)
unit_test: $(OBJECTS_TEST)
	$(CC) $(CFLAGS) -o $(EXE_TEST) $(OBJECTS_TEST)
main.o: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o main.o
my_string.o: $(IMPL)
	$(CC) $(CFLAGS) -c $(IMPL) -o my_string.o
generic_vector.o: $(GEN_IMPL)
	$(CC) $(CFLAGS) -c $(GEN_IMPL) -o generic_vector.o
unit_test.o: $(SRC_TEST)
	$(CC) $(CFLAGS) -c $(SRC_TEST) -o unit_test.o
test_def.o: $(IMPL_TEST)
	$(CC) $(CFLAGS) -c $(IMPL_TEST) -o test_def.o
clean_all:
	rm $(ALL_OBJECTS) $(EXE) $(EXE_TEST)
clean_string:
	rm $(OBJECTS) $(EXE) 
clean_test:
	rm $(OBJECTS_TEST) $(EXE_TEST)
