spell.exe: main.o hash.o
	g++ -o spell.exe main.o hash.o

main.o: main.cpp hash.h
	g++ -c main.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o spellDebug.exe main.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
