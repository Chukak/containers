# Compilers and flags
CCC = g++  
CXX = g++
BASICOPTS = -g -Wall -Werror -std=c++14 
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Target directory
TARGETDIR_containers=GNU-amd64-Linux
SRCDIR=src


all: $(TARGETDIR_containers)/containers

## Target: containers
CCFLAGS_containers = 
OBJS_containers =  \
	$(TARGETDIR_containers)/main.o \
	$(TARGETDIR_containers)/queue.o \
	$(TARGETDIR_containers)/stack.o 
	


$(TARGETDIR_containers)/containers: $(TARGETDIR_containers) $(OBJS_containers) 
	$(CXX) $(CXXFLAGS) $(CCFLAGS_containers) $(CPPFLAGS_containers) -o $@ $(OBJS_containers) $(LDLIBS_containers)

# Source files .o
$(TARGETDIR_containers)/main.o: $(TARGETDIR_containers) main.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_containers) $(CPPFLAGS_containers) -o $@ main.cpp
	
$(TARGETDIR_containers)/queue.o: $(TARGETDIR_containers) $(SRCDIR)/queue.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_containers) $(CPPFLAGS_containers) -o $@ $(SRCDIR)/queue.cpp
	
$(TARGETDIR_containers)/stack.o: $(TARGETDIR_containers) $(SRCDIR)/stack.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_containers) $(CPPFLAGS_containers) -o $@ $(SRCDIR)/stack.cpp

clean:
	rm -f \
		$(TARGETDIR_containers)/containers 
	$(CCADMIN)
	rm -f -r $(TARGETDIR_containers)


# Create target dorectory, if necessary
$(TARGETDIR_containers):
	mkdir -p $(TARGETDIR_containers)

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux
