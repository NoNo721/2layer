CC = nvcc
CXX = g++

CFLAGS = -g -O3 -std=c++11 -cudart static -gencode arch=compute_60,code=sm_60
CXXFLAGS = -g


src_CPP := $(wildcard *.cpp)
src_CU := $(wildcard *.cu)

obj_CPP := $(patsubst %.cpp, %.o, $(src_CPP))
obj_CU := $(patsubst %.cu, %.o, $(src_CU))


target := magnon.exe


all: $(target)


$(target): $(obj_CPP) $(obj_CU)
	$(CC) $(CFLAGS) -o $(target) $(obj_CPP) $(obj_CU)

$(obj_CU): $(src_CU) 
	$(CC) $(CFLAGS) -c $(src_CU)

$(obj_CPP): $(src_CPP)
	$(CXX) $(CXXFLAGS) -c $(src_CPP)


.PHONY: clean

clean:
	@rm -rf  $(target) $(obj_CPP) $(obj_CU)