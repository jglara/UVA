CXXFLAGS =	-O0 -g -Wall  -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE
OBJS =		462.o

LIBS =

TARGET =	462

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
