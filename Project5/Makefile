
hash: hash.o md5.o buffer.o
	gcc hash.o md5.o buffer.o -o hash   
   
hash.o:  hash.c md5.h buffer.h
	gcc -Wall -std=c99 -c -g hash.c

md5.o:  md5.c md5.h buffer.h
	gcc -Wall -std=c99 -g -c md5.c

buffer.o:   buffer.c md5.h buffer.h 
	gcc -Wall -std=c99 -g -c buffer.c

testdriver:   testdriver.c md5.c buffer.c
	gcc -Wall -std=c99 -g -DTESTABLE testdriver.c md5.c buffer.c -o testdriver  
     
clean:
	rm -f hash.o
	rm -f md5.o
	rm -f buffer.o
	rm -f testdriver
	rm -f hash
	rm -f output.txt
	rm -f stderr.txt

                        
