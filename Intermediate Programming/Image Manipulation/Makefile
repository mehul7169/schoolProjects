CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g -lm


# demo: demo_ppm.o ppm_io.o
# 	$(CC) demo_ppm.o ppm_io.o -o demo

project: project.o ppm_io.o image_Manip.o
	$(CC) project.o ppm_io.o image_Manip.o -o project -lm

project.o: project.c ppm_io.c image_Manip.c
	$(CC) $(CFLAGS) -c project.c -lm

# demo_ppm.o: demo_ppm.c ppm_io.h
# 	$(CC) $(CFLAGS) -c demo_ppm.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c -lm

image_Manip.o: image_Manip.c image_Manip.h
	$(CC) $(CFLAGS) -c image_Manip.c 


clean:
	rm -f *.o demo
