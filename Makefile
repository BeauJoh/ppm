ppm5233: main.o menuHandler.o sha1.o pc1Handler.o pc1.o filehandler.o
	g++ -o ppm5233 main.o menuHandler.o sha1.o pc1Handler.o pc1.o filehandler.o

main.o: main.cpp
	g++ -c main.cpp

menuHandler.o: menuHandler.cpp menuHandler.h
	g++ -c menuHandler.cpp

sha1.o: sha1.cpp sha1.h
	g++ -c sha1.cpp
	
pc1Handler.o: pc1Handler.cpp pc1Handler.h
	g++ -c pc1Handler.cpp

pc1.o: pc1.cpp pc1.h
	g++ -c pc1.cpp
	
filehander.o: filehandler.cpp filehandler.h
	g++ -c filehandler.cpp

clean:
	rm -f *.o ppm5233
