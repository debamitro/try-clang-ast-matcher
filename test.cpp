#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

class MyPrinter : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    ASTContext *Context = Result.Context;
    if (const CallExpr *E =
        Result.Nodes.getNodeAs<clang::CallExpr>("functions")) {
      FullSourceLoc FullLocation = Context->getFullLoc(E->getLocStart());
      if (FullLocation.isValid()) {
        llvm::outs() << "Found call at " << FullLocation.getSpellingLineNumber()
                     << ":" << FullLocation.getSpellingColumnNumber() << "\n";
      }
    }
  }
};

int main(int argc, const char **argv) {
  llvm::cl::OptionCategory MyToolCategory("my-tool options");
  
  // parse the command-line args passed to your code
  CommonOptionsParser op(argc, argv, MyToolCategory);
  // create a new Clang Tool instance (a LibTooling environment)
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());

  MyPrinter Printer;
  MatchFinder Finder;

  StatementMatcher functionMatcher =
    callExpr(callee(functionDecl(hasName("printf")))).bind("functions");

  Finder.addMatcher(functionMatcher, &Printer);
    
  // run the Clang Tool, creating a new FrontendAction (explained below)
  int result = Tool.run(newFrontendActionFactory(&Finder).get());

  return result;
}
