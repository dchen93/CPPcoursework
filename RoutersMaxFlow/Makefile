router.out : router.o routeRunner.o  
	g++ -ansi -Wall -g -o router.out router.o routeRunner.o  

router.o : router.cpp router.h BinaryHeap.h dsexceptions.h 
	g++ -ansi -Wall -g -c router.cpp

routeRunner.o : routeRunner.cpp CPUTimer.h router.h 
	g++ -ansi -Wall -g -c routeRunner.cpp

clean : 
	rm -f router.out router.o  routeRunner.o   
