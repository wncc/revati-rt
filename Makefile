CC     = g++
CFLAGS = -std=c++11
TARGET = loadxml
LINK = tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp

all: 
	$(CC) $(CFLAGS) -o $(TARGET) src/$(TARGET).cpp $(LINK)
	./loadxml

clean: 
	$(RM) $(TARGET)