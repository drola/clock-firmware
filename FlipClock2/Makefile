CXX=g++
CXXFLAGS=-g -Wall -I./ -DTEST

CXX_AVR=avr-g++
CXXFLAGS_AVR=-Wall -mmcu=atmega324pa -DF_CPU=8000000UL -I./

AVRDUDE=avrdude -p m324pa -c usbasp

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

avr_src = $(wildcard *.cpp)
avr_obj = $(src:.cpp=.avr.o)
avr_dep = $(obj_avr:.avr.o=.avr.d)

test_src = $(wildcard tests/*.cpp)
test_obj = ${test_src:.cpp=.o} ${obj}
test_dep = $(test_obj:.o=.d)  # one dependency file for each source

-include $(dep)   # include all dep files in the makefile
-include $(avr_dep)
-include ${test_dep}

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
# sed Replaces **.o with **.o **.dep
%.d: %.cpp
	@set -ex; rm -f $@; \
		$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

%.avr.d: %.cpp
	@set -ex; rm -f $@; \
		$(CXX_AVR) $(CXXFLAGS_AVR) $< -MM -MT $(@:.d=.o) > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.avr.o: %.cpp
	$(CXX_AVR) $(CXXFLAGS_AVR) -o $@ -c $<

test: ${test_obj}
	$(CXX) -o $@ $^
	./test

avr.hex: ${avr_obj}
	$(CXX_AVR) -o $@ $^

clean:
	rm -f avr.hex ${test_dep} ${test_obj} ${avr_dep} ${avr_obj} test ${dep} ${obj}

chip_backup:
	${AVRDUDE} -U flash:r:backup.hex:i

chip_upload:
	${AVRDUDE} -U flash:w:avr.hex:i

.PHONY: test clean chip_backup chip_upload
