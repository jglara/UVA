CXXFLAGS =	-O0 -g -Wall  -lm -lcrypt -std=c++11 -pipe -DONLINE_JUDGE
OBJS =		uva10189.o

LIBS =

TARGET =	uva10189

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
