CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		11402.o

LIBS =

TARGET =	11402

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
