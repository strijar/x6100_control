CC = arm-linux-gnueabihf-gcc
CFLAGS = -I. -O2

APP = x6100_control_test

OBJS = test_vfo.o x6100_control.o

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(APP)

clean:
	rm *.o $(APP)
