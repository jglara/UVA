CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =		100.o

LIBS =

TARGET =	100

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
