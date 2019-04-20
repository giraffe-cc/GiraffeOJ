oj_server:oj_server.cc oj_model.hpp oj_view.hpp 
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp -lctemplate \
	-I ~/third_part/include -L ~/third_part/lib

server:server.cpp compile.hpp 
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp

test:test.cpp
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp

.PHONY:clean
clean:
	rm oj_sever server test
