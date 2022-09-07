CC = arm-linux-gnueabihf-gcc
CFLAGS = -I. -O2

APP = test_vfo

LIB_OBJS = x6100_control.o x6100_flow.o x6100_gpio.o
APP_OBJS = $(APP).o

all: $(APP)

$(APP): $(LIB_OBJS) $(APP_OBJS)
	$(CC) $(LDFLAGS) $(LIB_OBJS) $(APP_OBJS) -o $(APP)

clean:
	rm *.o $(APP)
