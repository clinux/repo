# Automatic Makefile
# https://github.com/clinux
# [include/]  src/
# put .c and Makefile in src;
# put .h in include (they can be in src)
# .cpp, CXX, CXXFLAGS for C++;
# CPPFLAGS for header include directory
 
OUT      = main.out
SRC      = $(wildcard *.c)
OBJ      = $(patsubst %.c,%.o,$(SRC))
CC       = gcc
CXX      = g++
CFLAGS   = -std=c99 -Wall -W
CXXFLAGS = -std=c++0x -Wall -W
CPPFLAGS = -I ../include
LDFLAGS  =
 
#CFLAGS  += -g
#CFLAGS  += -DNDEBUG
#CFLAGS  += -D_POSIX_SOURCE -D_BSD_SOURCE
#LDFLAGS += -lpthread
 
$(OUT): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@
 
include $(SRC:.c=.d)
 
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
 
.PHONY: clean
clean:
	rm *.d *.d.* $(OBJ) $(OUT)
