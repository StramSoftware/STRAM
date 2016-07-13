ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

CXXFLAGS  := -g -Wall -fPIC
ROOTFLAGS := `root-config --cflags --glibs`
ROOTCFLAGS := `root-config --cflags`

all: obj STRAM 

STRAM: obj/STRAM.o obj/AbsorptionMap.o obj/AbsorptionMapDict.o
	@echo "Linking $@"
	@g++ $(CXXFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS) $^ -o $@ && echo $@ done

libAbsorptionMap.so: obj/AbsorptionMap.o obj/AbsorptionMapDict.o
	@echo "Compiling $@"
	g++  -shared $(ROOTGLIBS) $(ROOTCFLAGS) $^ -o $@

obj/STRAM.o: src/STRAM.cpp
	@echo "Compiling $@"
	@g++ -c $(ROOTCFLAGS) $< -o $@

obj/AbsorptionMapDict.o: AbsorptionMapDict.cxx AbsorptionMapDict.h
	@echo "Compiling $@"
	@g++ -c $(CXXFLAGS) $< $(ROOTCFLAGS) -o $@

obj/%.o: src/%.cpp src/%.h
	@echo "Compiling $@"
	g++ -I ../../macros/STRAM/src -c $(CXXFLAGS) $(ROOTCFLAGS) $< -o $@

AbsorptionMapDict.cxx: src/AbsorptionMap.h src/LinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint  -f $@ -c $^

doc:	libAbsorptionMap.so
	@root -b -q src/makedoc.C

obj:
	@test -d obj || mkdir obj

run: STRAM
	./STRAM FEB1.root FEB2.root FEB3.root FEB4.root FEB5.root 

clean:
	@rm -fv obj/*  *~ STRAM AbsorbtionMapDict.h AbsorbtionMapDict.cxx libAbsorptionMap.so

backup:
	@tar jcf  STRAM.`date +%y%m%d%H`.tar.bz2 src Makefile --exclude="*~"

test:
	echo `ls`
