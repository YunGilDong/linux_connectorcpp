#
# Environment
#
MARIADB_INC = /usr/include/cppconn
MARIADB_INC2 = /usr/local/include
MARIADB_LIB = 

CCOPTS = -c -Wno-write-strings -I$(MARIADB_INC) -I$(MARIADB_INC2)
#LDOPTS = -L$(MARIADB_LIB)
LDOPTS = 

CC = g++ $(CCOPTS)
LINK = g++ $(LDOPTS)
.cpp.o:	; $(CC) $<
LIBS = -lmysqlcppconn

OBJS = DBProc.o ClsMariaDBcpp.o

TARGET = DBProc

default:	$(TARGET)

$(TARGET):	$(OBJS)
	$(LINK) $(OBJS) -o $@ $(LIBS)