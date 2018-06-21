# Compilers 
CCC = g++  
CXX = g++
# Flags
BASICOPTS = -g -Wall -Werror -std=c++14 -fPIC 
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
# Linking flags
LDFLAGS = -shared 
CCADMIN = 

.PHONY: all clean

# Target directory
TARGETDIR=containers
# Directory for object files `.o`
OBJS=$(TARGETDIR)/ofiles
# queue/queue.so
QUEUEDIR=$(TARGETDIR)/queue
# stack/stack.so
STACKDIR=$(TARGETDIR)/stack
# sorted_list/sorted-list.so
SLISTDIR=$(TARGETDIR)/sorted_list
# bst/bst.so
BSTDIR=$(TARGETDIR)/bst
# Sources files
SOURCES=src


all: compile copy end 

# Compile all the sources files
compile: $(QUEUEDIR)/queue.so $(STACKDIR)/stack.so $(SLISTDIR)/sorted_list.so $(BSTDIR)/bst.so

# queue
$(QUEUEDIR)/queue.so: $(QUEUEDIR) $(OBJS)/queue.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)/queue.o $(LDFLAGS)

$(OBJS)/queue.o: $(OBJS) $(SOURCES)/queue.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SOURCES)/queue.cpp

# stack
$(STACKDIR)/stack.so: $(STACKDIR) $(OBJS)/stack.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)/stack.o $(LDFLAGS)

$(OBJS)/stack.o: $(OBJS) $(SOURCES)/stack.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SOURCES)/stack.cpp

# sorted list
$(SLISTDIR)/sorted_list.so: $(SLISTDIR) $(OBJS)/sorted_list.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)/sorted_list.o $(LDFLAGS)

$(OBJS)/sorted_list.o: $(OBJS) $(SOURCES)/sorted_list.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SOURCES)/sorted_list.cpp

# binary search tree
$(BSTDIR)/bst.so: $(BSTDIR) $(OBJS)/bst.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)/bst.o $(LDFLAGS)

$(OBJS)/bst.o: $(OBJS) $(SOURCES)/bst.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SOURCES)/bst.cpp
	

clean:
	rm -f $(TARGETDIR)/containers 
	$(CCADMIN)
	rm -f -r $(TARGETDIR)

# Copy all the header files 
copy:
	cp src/queue.h $(QUEUEDIR)/
	cp src/stack.h $(STACKDIR)/
	cp src/sorted_list.h $(SLISTDIR)/
	cp src/bst.h $(BSTDIR)/

# Remove all the objects files
end:
	rm $(OBJS)/queue.o
	rm $(OBJS)/stack.o
	rm $(OBJS)/sorted_list.o
	rm $(OBJS)/bst.o
	rm -r -f $(OBJS)
	
# Create directories, if necessary
$(TARGETDIR):
	mkdir -p $(TARGETDIR)

$(OBJS):
	mkdir -p $(OBJS)

$(QUEUEDIR):
	mkdir -p $(QUEUEDIR)

$(STACKDIR):
	mkdir -p $(STACKDIR)

$(SLISTDIR):
	mkdir -p $(SLISTDIR)

$(BSTDIR):
	mkdir -p $(BSTDIR)

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux
