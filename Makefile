SRC = application_layer.c data_link.c  stateMachine.c reader.c writer.c utilities.c

all:
	gcc $(SRC) -Wall -o serial

debug:
	gcc -g $(SRC) -Wall -o serial

clean:
	rm serial
