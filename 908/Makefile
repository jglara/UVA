CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		908.o

LIBS =

TARGET =	908

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
