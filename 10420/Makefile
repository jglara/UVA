CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		10420.o

LIBS =

TARGET =	10420

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
