objs= test.o Game.o Version.o Libraries.o System.o Utils/Tools.o

objs4http = test4http.o Utils/HttpR.o Utils/Tools.o User.o

test4http : $(objs4http)
	g++ -o test4http $(objs4http) -lcurl

test4http.o : test4http.cpp

Utils/HttpR.o : Utils/HttpR.cpp

Utils/Tools.o : Utils/Tools.cpp

User.o : User.cpp

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
	rm go test4http $(objs) $(objs4http)
