#include <execinfo.h>
#include <unistd.h>
#include <string.h>
#include <csignal>

#include <iostream>
#include <list>
#include <array>

class BTrace {
  static void Handler(int sig) {

    std::cerr << "\n--== BTrace ==--";
    std::cerr << "\n: Sig: " << strsignal(sig);

    try {
      throw;
    } catch (const std::exception &e) {
      std::cerr << "\n: Unhandled exception. what(): "
        << e.what() << "\n\n";
    } catch (...) {
      std::cerr << "\n: Unhandled exception.\n\n";
    }

    std::array<void*, 20> trace;
    size_t size = backtrace(trace.data(), trace.size());
    backtrace_symbols_fd(trace.data(), size, STDERR_FILENO);
  }

  public:
    enum class S {
      ABRT = SIGABRT,
      SEGV = SIGSEGV,
    };

    BTrace(const std::list<S> t = { S::ABRT, S::SEGV }) {
      for (auto&& e : t) std::signal(unsigned(e), Handler);
    }

   ~BTrace() {}
};
