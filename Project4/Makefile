schedule: schedule.o volunteer.o
	gcc schedule.o volunteer.o  -o schedule
    
schedule.o:  schedule.c volunteer.h
	gcc -Wall -std=c99 -c -g schedule.c

volunteer.o:  volunteer.c volunteer.h
	gcc -Wall -std=c99 -g -c volunteer.c
    

    
clean:
	rm -f chop.o
	rm -f edit.o
	rm -f text.o
	rm -f chop
	rm -f output.txt
	rm -f stderr.txt
	rm -f stdout.txt
