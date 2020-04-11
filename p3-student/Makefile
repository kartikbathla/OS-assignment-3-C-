CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++14

MKDIR_P = mkdir -p
OBJ_DIR = obj

OBJS = obj/main.o obj/BoundedBuffer.o obj/ProducerConsumer.o

all: prodcon prodcon_tests submission

prodcon : $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

submission:
	zip -r prodcon-submission.zip src

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/%.o: src/%.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

obj/prodcon_tests.o: test/prodcon_tests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

prodcon_tests: obj/BoundedBuffer.o obj/ProducerConsumer.o obj/prodcon_tests.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	rm -f prodcon prodcon_tests output.txt
	rm -f *~ *.zip
	rm -rf obj
