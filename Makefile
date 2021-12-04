#Derry Brennan 26/10/2020
#Makefile for lab2
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.


CC = g++
CFLAGS = -std=c++11 -fopenmp
OBJFILES = multiThreadPrimePair.o
#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(OBJFILES)
	$(CC) -o multiThreadPrimePair $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG -Wall
DEBUG: ALL

doc: doxygen Doxyfile

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
