#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc 
GTK1 = `pkg-config --cflags gtk+-3.0`
GTK2 = `pkg-config --libs gtk+-3.0`
# define any compile-time flags
CFLAGS	:= -Wall -Wextra -g -DDEBUG -rdynamic

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -lconfig -lpthread

# define output directory
OUTPUT	:= output

# define source directory
CLIENTSRC := src/client
SERVERSRC := src/server 

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
CLIENTMAIN	:= client
SERVERMAIN	:= server
CLIENTSOURCEDIRS	:= $(shell find $(CLIENTSRC) -type d)
SERVERSOURCEDIRS	:= $(shell find $(SERVERSRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
CLIENTSOURCES		:= $(wildcard $(patsubst %,%/*.c, $(CLIENTSOURCEDIRS)))
SERVERSOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SERVERSOURCEDIRS)))

# define the C object files 
CLIENTOBJECTS		:= $(CLIENTSOURCES:.c=.o)
SERVEROBJECTS		:= $(SERVERSOURCES:.c=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

CLIENTOUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(CLIENTMAIN))
SERVEROUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(SERVERMAIN))

all: $(OUTPUT) $(CLIENTMAIN) $(SERVERMAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(CLIENTMAIN): $(OUTPUT) $(CLIENTOBJECTS) 
	$(CC) $(CFLAGS) $(GTK1) $(INCLUDES) -o $(CLIENTOUTPUTMAIN) $(CLIENTOBJECTS) $(LFLAGS) $(LIBS) $(GTK2)

$(SERVERMAIN): $(OUTPUT) $(SERVEROBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(SERVEROUTPUTMAIN) $(SERVEROBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(GTK1) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) -R $(OUTPUT)
	$(RM) $(call FIXPATH,$(CLIENTOBJECTS))
	$(RM) $(call FIXPATH,$(SERVEROBJECTS))
	@echo Cleanup complete!

#run: all
#	./$(OUTPUTMAIN)
#	@echo Executing 'run: all' complete!