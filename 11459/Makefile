CXXFLAGS =	-O0 -g -Wall  -lm -lcrypt -std=c++11 -pipe -DONLINE_JUDGE
OBJS =		11459.o

LIBS =

TARGET =	11459

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
