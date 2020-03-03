objs= test.o Game.o Version.o Libraries.o System.o Utils/Tools.o Utils/HttpR.o Utils/Args.o User.o

objs4http = test4http.o Utils/HttpR.o Utils/Tools.o User.o

test4http : $(objs4http)
	g++ -o test4http $(objs4http) -lcurl

test4http.o : test4http.cpp

Utils/HttpR.o : Utils/HttpR.cpp

Utils/Args.o : Utils/Args.cpp
	g++ -c -o Utils/Args.o -std=c++11 Utils/Args.cpp

Utils/Tools.o : Utils/Tools.cpp

User.o : User.cpp

go : $(objs)
	g++ -g -o go $(objs) -lcurl

test.o : test.cpp
	g++ -c -o test.o -std=c++11 test.cpp

Game.o : Game.h

Version.o : Version.h Version.cpp
	g++ -c -o Version.o -std=c++11 Version.cpp

Libraries.o : Libraries.h

System.o : System.h

clean :
	rm go test4http $(objs) $(objs4http)
