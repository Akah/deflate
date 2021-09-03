OBJS 	:= $(patsubst %.c,%.o,$(wildcard *.c))
WARN 	:= -Werror -Wall -Wextra
TARG 	:= deflate
OS   	:= $(shell uname)
CFLAGS  := -g
CFLAGS 	+= -Dtime="\"$(shell date --utc +%Y-%m-%dT%H:%M:%SZ)\""
CFLAGS  += -Dbuild="\"$(shell uname -svrpo)\""
CFLAGS  += -Dtarget="\"$(TARG)\""
CFLAGS  += -Dversion="\"0.1.0\""

ifeq ($(OS),$(filter $(OS),Windows_NT CYGWIN_NT-10.0))
# LIBS 	:= -lm -mwindows
	SUFFIX	:= .exe
	CC	:= gcc
else
	LIBS 	:=
endif

ifeq ($(TARGET),Windows_NT)
ifeq ($(OS),Linux))
	CC	:= x86_64-w64-mingw32-gcc
endif
endif

$(info OS host: $(OS))
ifdef ($(TARGET))
	$(info Cross compiling: $(XC))
endif

repl: $(OBJS)
	$(CC) $(CFLAGS) $(WARN) -o $(TARG) $(OBJS) $(LIBS)
	@echo Sucessfully built file: $(TARG)$(SUFFIX)

lib: $(OBJS)
	$(CC) -shared -o $(TARG) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(TARG)

install:
	sudo cp $(TARG) /usr/bin

uninstall:
	sudo rm /usr/bin/$(TARG)

.PHONY: $(TARG) clean lib install uninstall
