.SUFFIXES: .cpp .h
CC := g++
RM := rm
LINK := tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp
TARGET := raytracer
ROOT :=.
SRCDIR := $(ROOT)/src
INCDIR := $(ROOT)/include
SCENE := scenes/shadow.xml
IMAGE := image.ppm
CPPFLAGS := -I$(INCDIR)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))
DEPS := $(patsubst %.cpp,%.d,$(filter %.cpp,$(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LINK)

-include -include $(OBJS:.o=.d)

$(OBJS): %.o : %.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) -rf *~ $(OBJS) $(DEPS) $(SRCDIR)/*~