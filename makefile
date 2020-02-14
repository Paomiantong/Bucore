objs= test.o Game.o Version.o Libraries.o System.o

go : $(objs)
	g++ -o go $(objs)

test.o : test.cpp
	g++ -c -o test.o -std=c++11 test.cpp

Game.o : Game.h

Version.o : Version.h Version.cpp
	g++ -c -o Version.o -std=c++11 Version.cpp

Libraries.o : Libraries.h

System.o : System.h

clean :
	rm go $(objs)
