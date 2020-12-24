#include "dispatcher_utility.hpp"
#include "grabber/main/agent.hpp"
#include "grabber/main/daemon.hpp"
#include <pqrs/osx/process_info.hpp>

int main(int argc, const char* argv[]) {
  //
  // Initialize
  //

  auto scoped_dispatcher_manager = krbn::dispatcher_utility::initialize_dispatchers();

  signal(SIGUSR1, SIG_IGN);
  signal(SIGUSR2, SIG_IGN);

  pqrs::osx::process_info::enable_sudden_termination();

  //
  // Check euid
  // (grabber is launched from LaunchDaemons (root) and LaunchAgents (user).)
  //

  bool root = (geteuid() == 0);

  if (root) {
    return krbn::grabber::main::daemon();
  } else {
    return krbn::grabber::main::agent();
  }
}
