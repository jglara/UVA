CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		146.o

LIBS =

TARGET =	146

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
