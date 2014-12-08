CC = clang
CFLAGS = -Wall -O0 -g -std=c99
LFLAGS = -O0 -g
LIBS = -lgsl  -lgslcblas -lm

sum: part_three.o 
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

sum_data: sum
	./sum > sum_data


clean : 
	rm -f *~
	rm -f *.o
	rm -f part_three

veryclean : clean
	rm -f part_three
