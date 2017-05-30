
CXXFLAGS := $(shell llvm-config --cxxflags)
LXXFLAGS := \
    -lclangFrontend \
    -lclangParse \
    -lclangSema \
    -lclangASTMatchers \
    -lclangAST \
    -lclangAnalysis \
    -lclangDriver \
    -lclangEdit \
    -lclangFrontendTool \
    -lclangLex \
    -lclangEdit \
    -lclangRewrite \
    -lclangRewriteFrontend \
    -lclangStaticAnalyzerFrontend \
    -lclangStaticAnalyzerCheckers \
    -lclangStaticAnalyzerCore \
    -lclangSerialization \
    -lclangTooling \
    -lclangFormat \
    -lclangBasic \
    -lclangToolingCore \
    $(shell llvm-config --ldflags --libs --system-libs) 

all: test_tool

clean:
	\rm -f *.o test_tool

test_tool: test.o
	clang++ $< $(CXXFLAGS) $(LXXFLAGS) -o $@
%.o: %.cpp
	clang++ $< $(CXXFLAGS) -c
