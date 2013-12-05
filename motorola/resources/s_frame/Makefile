# Make for C compiling

CFLAGS=-W -Wall

ZIP_NAME=serialframe.zip

DEPLOY_TARGET=vili.pmmf.hu:public_html/c/serialframe

BIN=bin/Debug/serialframe


OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

$(BIN):$(OBJS)
	$(CC) -o$(BIN) $(OBJS)
	$(BIN)

%.o:%.c 
	$(CC) -c $< -o $@ $(CFLAGS)

doc:
	doxygen

clean:
	$(RM) *~
	$(RM) obj/Debug/*
	$(RM) html/*
	$(RM) *.o
	$(RM) $(BIN)

zip:clean
	zip $(ZIP_NAME) *

deploy:zip
	scp $(ZIP_NAME) $(DEPLOY_TARGET)
help:
	@echo "no parameter: 	compile and run"
	@echo "doc:		create documentation"
	@echo "zip:		create a zip with sources"
	@echo "deploy:		copy created zip sources to my home"
	@echo "clean:		clean uneccesary files"
	@echo "help:		this screen"

.PHONY:clean doc help
