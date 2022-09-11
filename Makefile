CC = arm-none-linux-gnueabihf-gcc
CXX = arm-none-linux-gnueabihf-g++
CFLAGS += -I. -O2
LDFLAGS += -lwampcc -lwampcc_json -ljansson -luv -lssl -lcrypto -lpthread -lm

APP = x6100_server

LIB_OBJS = x6100_control.o x6100_flow.o x6100_gpio.o
APP_OBJS = $(APP).o x6100_server_rpc.o

all: $(APP)

$(APP): $(LIB_OBJS) $(APP_OBJS)
	$(CXX) $(LDFLAGS) $(LIB_OBJS) $(APP_OBJS) -o $(APP)

clean:
	rm *.o $(APP)
