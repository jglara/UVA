CXXFLAGS =	-O0 -g -Wall  -lm -lcrypt -std=c++11 -pipe -DONLINE_JUDGE
OBJS =		299.o

LIBS =

TARGET =	299

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
