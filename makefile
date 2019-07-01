main.exe: main.o A.h D.h S.h W.H save.h autorecover.h autorecover1.h autorecover2.h feasibility.h read.h test.h test1.h test2.h
	g++ main.o -o main.exe
main.o: main.cpp A.h D.h S.h W.H save.h autorecover.h autorecover1.h autorecover2.h feasibility.h read.h test.h test1.h test2.h
	g++ -c main.cpp -o main.o 