CXX=g++ -DWIN32 -I/usr/local/include -L/usr/local/lib -g 

supra : main.o index.o
	$(CXX) -o supra main.o index.o -static -lsqlite -lwebserver

main.o : main.cpp main.h
	 $(CXX) -c main.cpp

index.o : index.cpp main.h parts.h
	  $(CXX) -c index.cpp

clean :
	rm supra *.o	