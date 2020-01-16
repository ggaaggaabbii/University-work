# This Makefile is designed to be simple and readable.  It does not
# aim at portability.  It requires GNU Make.

BASE = calc++
BISON = /usr/local/Cellar/bison/3.5/bin/bison
CXX = g++ -std=c++11
FLEX = flex
XSLTPROC = xsltproc
BISONFLAGS = -v

all: $(BASE)

%.cpp %.h %.xml %.gv: %.yy
	$(BISON) $(BISONFLAGS) -v --xml --graph=$*.gv -o $*.cpp $<

%.cpp: %.ll
	$(FLEX) $(FLEXFLAGS) -o$@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<

$(BASE): $(BASE).o driver.o parser.o scanner.o
	$(CXX) -o $@ $^

$(BASE).o: parser.h
parser.o: parser.h
scanner.o: parser.h

run: $(BASE)
	@echo "Type arithmetic expressions.  Quit with ctrl-d."
	./$< -

html: parser.html
%.html: %.xml
	$(XSLTPROC) $(XSLTPROCFLAGS) -o $@ $$($(BISON) --print-datadir)/xslt/xml2xhtml.xsl $<

CLEANFILES =										\
  $(BASE) *.o										\
  parser.hpp parser.cpp parser.output parser.xml parser.html parser.gv location.hh	\
  scanner.cpp
clean:
	rm -f $(CLEANFILES)
