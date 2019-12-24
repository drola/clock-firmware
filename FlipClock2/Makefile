CXX=g++
CXXFLAGS=-g -I./ -DTEST

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

test_src = $(wildcard tests/*.cpp)
test_obj = ${test_src:.cpp=.o} ${obj}
test_dep = $(test_obj:.o=.d)  # one dependency file for each source

-include $(dep)   # include all dep files in the makefile
-include ${test_dep}

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
# sed Replaces **.o with **.o **.dep
%.d: %.cpp
	@set -ex; rm -f $@; \
		$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test: ${test_obj}
	$(CXX) -o $@ $^
	./test

clean:
	rm -f ${test_dep} ${test_obj} test ${dep} ${obj}
	
.PHONY: test clean
