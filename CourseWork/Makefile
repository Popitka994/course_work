CC := g++
CFLAGS := -Wall -std=c++11
LDFLAGS := -lssl -lcrypto

SOURCES := main.cpp server.cpp auth.cpp errors.cpp

OBJECTS := $(SOURCES:.cpp=.o)

EXECUTABLE := my_server

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
