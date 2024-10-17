college: college.o dataset.o 
	gcc $^ -o college
	./college
college.o: college.c dataset.h
	gcc -c $<
dataset.o: dataset.c dataset.h
	gcc -c $<