CXX = g++
CXXFLAGS = -Wall -O3 -std=c++0x -march=native
#CXXFLAGS = -Wall -g -std=c++0x -march=native

# comment the following flags if you do not want to SSE instructions
 DFLAG += -DUSESSE
#DFLAG += pedantic

# comment the following flags if you do not want to use OpenMP
DFLAG += -DUSEOMP
CXXFLAGS += -fopenmp

all: ffm-train weight-server

ffm-train: ffm-train.cpp ffm.o timer.o cJSON.o 
	$(CXX) $(CXXFLAGS) $(DFLAG) -o $@ $^

weight-server: weight-server.cpp ffm.o timer.o cJSON.o
	$(CXX) $(CXXFLAGS) $(DFLAG) -o $@ $^ -lhttpcpp

ffm.o: ffm.cpp ffm.h timer.o cJSON.o
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

cJSON.o: cJSON.c cJSON.h 
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

timer.o: timer.cpp timer.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

clean:
	rm -f ffm-train weight-server ffm.o timer.o cJSON.o
