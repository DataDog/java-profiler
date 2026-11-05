// Copyright 2026, Datadog, Inc.

// Standalone validation harness for the malloc-shim signal-allocation
// detector (libdebug.so). Runs as two modes:
//
//   malloc_shim_validate --control   # without LD_PRELOAD: pins the contract
//                                    # that nothing is resolvable and Shims
//                                    # stays a silent no-op
//   LD_PRELOAD=.../libdebug.so malloc_shim_validate   # full detection matrix
//   malloc_shim_validate --full       # same as no-args: explicit full mode
//
// Any other argument is a usage error (exit 2). Exit codes: 0 = pass,
// 1 = failures, 2 = usage error.
//
// The full mode forks one child per detection case: the child registers a tid
// (raw dlsym'd setter, or Shims::setSighandlerTid - the production wiring
// chain), allocates, and the parent asserts the child died with SIGSEGV and
// that the shim's stderr marker was emitted.
//
// The Shims variant compiles in the production debugSupport.cpp, so a broken
// dlsym lookup or CAS in Shims fails this harness even when the shim itself
// is sound.

#include <stddef.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debugSupport.h"

typedef void (*SetSighandlerTidFn)(int);

static const char *const kMarker = "!!!! MALLOC in signal handler !!!";
// Above the Linux pid_max ceiling (2^22), so it can never match a live tid.
static const int kBogusTid = 1 << 30;

static pid_t my_tid() {
  return (pid_t)syscall(__NR_gettid);
}

static SetSighandlerTidFn find_setter() {
  return reinterpret_cast<SetSighandlerTidFn>(dlsym(RTLD_DEFAULT, "set_sighandler_tid"));
}

static int g_failures = 0;

static void report(int ok, const char *what) {
  printf("%s %s\n", ok ? "PASS" : "FAIL", what);
  if (!ok) {
    g_failures++;
  }
}

// Allocates a pattern-filled block and verifies it reads back. Returns NULL
// on any mismatch so callers can treat "allocated but corrupt" as a failure.
static void *alloc_and_check(size_t size) {
  unsigned char *p = (unsigned char *)malloc(size);
  if (p == NULL) {
    return NULL;
  }
  memset(p, 0x5a, size);
  for (size_t i = 0; i < size; i++) {
    if (p[i] != 0x5a) {
      free(p);
      return NULL;
    }
  }
  return p;
}

// Runs `body` in a forked child. The child's stderr is redirected to a fresh
// temp file whose path is stored in `marker_path` (truncated to empty first).
// The fd must stay open in the parent across the fork: the child dups it onto
// stderr. Returns the raw wait status.
static int run_in_child(char *marker_path, size_t marker_path_size, void (*body)()) {
  marker_path[0] = '\0';
  char tmpl[] = "/tmp/malloc_shim_validate_XXXXXX";
  int fd = mkstemp(tmpl);
  if (fd < 0) {
    return -1;
  }
  if (ftruncate(fd, 0) != 0) {
    close(fd);
    unlink(tmpl);
    return -1;
  }
  fflush(NULL); // drop inherited stdio buffers before forking
  pid_t pid = fork();
  if (pid < 0) {
    close(fd);
    unlink(tmpl);
    return -1;
  }
  if (pid == 0) {
    dup2(fd, STDERR_FILENO);
    close(fd);
    body();
    _exit(0); // body() must terminate the child itself
  }
  close(fd);
  int st = 0;
  while (waitpid(pid, &st, 0) < 0) {
    if (errno != EINTR) {
      unlink(tmpl);
      return -1;
    }
  }
  snprintf(marker_path, marker_path_size, "%s", tmpl);
  return st;
}

static const char *wait_status_desc(int st) {
  static char desc[64];
  if (WIFSIGNALED(st)) {
    snprintf(desc, sizeof(desc), "killed by signal %d", WTERMSIG(st));
  } else if (WIFEXITED(st)) {
    snprintf(desc, sizeof(desc), "exit code %d", WEXITSTATUS(st));
  } else {
    snprintf(desc, sizeof(desc), "raw status %d", st);
  }
  return desc;
}

static bool child_died_of_sigsegv(int st) {
  return WIFSIGNALED(st) && WTERMSIG(st) == SIGSEGV;
}

static int child_exited_with(int st, int code) {
  return WIFEXITED(st) && WEXITSTATUS(st) == code;
}

// Reads the child's captured stderr, reports its contents, removes the file,
// and returns whether the child died of SIGSEGV with the shim's marker
// emitted. Always prints the evidence so a failed case leaves it in the log.
static bool check_detection(int st, const char *marker_path) {
  bool died = child_died_of_sigsegv(st);
  bool marker = false;
  if (marker_path[0] != '\0') {
    FILE *f = fopen(marker_path, "r");
    unlink(marker_path); // remove the temp file even if the read below fails
    if (f != NULL) {
      char buf[256];
      size_t n = fread(buf, 1, sizeof(buf) - 1, f);
      fclose(f);
      buf[n] = '\0';
      marker = strstr(buf, kMarker) != NULL;
      printf("  child stderr: [%s]\n", buf);
    }
  }
  if (!died || !marker) {
    printf("  child %s\n", wait_status_desc(st));
  }
  return died && marker;
}

// Writes a NUL-terminated string to stderr without stdio: legal after the
// tid is registered, where any malloc would trip the detector.
static void write_raw(const char *s) {
  ssize_t rc = write(STDERR_FILENO, s, strlen(s));
  (void)rc;
}

// --- cases ---

static void body_detect_raw() {
  SetSighandlerTidFn setter = find_setter();
  if (setter == NULL) {
    write_raw("child: setter not resolvable\n");
    _exit(2);
  }
  setter(my_tid());
  void *p = malloc(64);
  (void)p;
  write_raw("child: ALLOC-SURVIVED\n");
  _exit(1);
}

static void body_no_false_positive() {
  SetSighandlerTidFn setter = find_setter();
  if (setter == NULL) {
    _exit(2);
  }
  setter(kBogusTid);
  for (int i = 0; i < 16; i++) {
    if (alloc_and_check(1024) == NULL) {
      _exit(1);
    }
  }
  _exit(0);
}

static void body_reset_disables() {
  SetSighandlerTidFn setter = find_setter();
  if (setter == NULL) {
    _exit(2);
  }
  setter(my_tid());
  setter(-1);
  if (alloc_and_check(512) == NULL) {
    _exit(1);
  }
  _exit(0);
}

static void handler_mallocs(int sig) {
  (void)sig;
  void *p = malloc(16);
  (void)p;
  // If the shim misses, control returns here: report survival without stdio.
  write_raw("child: HANDLER-ALLOC-SURVIVED\n");
}

static void body_detect_in_signal_handler() {
  SetSighandlerTidFn setter = find_setter();
  if (setter == NULL) {
    _exit(2);
  }
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handler_mallocs;
  if (sigaction(SIGUSR1, &sa, NULL) != 0) {
    _exit(2);
  }
  setter(my_tid());
  raise(SIGUSR1);
  _exit(1); // reached only when the handler returned without tripping the shim
}

static void body_detect_via_shims() {
  Shims::instance().setSighandlerTid(my_tid());
  void *p = malloc(64);
  (void)p;
  write_raw("child: ALLOC-SURVIVED\n");
  _exit(1);
}

int main(int argc, char **argv) {
  bool control = false;
  bool full = (argc == 1); // no args stays full mode: gradle validateFull runs the binary with zero args
  if (argc == 2) {
    if (strcmp(argv[1], "--control") == 0) {
      control = true;
    } else if (strcmp(argv[1], "--full") == 0) {
      full = true;
    } else {
      fprintf(stderr, "usage: %s [--control|--full]\n", argv[0]);
      return 2;
    }
  } else if (argc > 2) {
    fprintf(stderr, "usage: %s [--control|--full]\n", argv[0]);
    return 2;
  }
  SetSighandlerTidFn setter = find_setter();

  if (control) {
    report(setter == NULL, "control: set_sighandler_tid not resolvable without libdebug.so");
    Shims::instance().setSighandlerTid(my_tid());
    void *p = alloc_and_check(256);
    report(p != NULL, "control: Shims::setSighandlerTid is a silent no-op, allocation works");
    free(p);
  } else if (full) {
    report(setter != NULL, "full: set_sighandler_tid resolvable via dlsym(RTLD_DEFAULT)");
    if (setter == NULL) {
      printf("FAIL full: detector cannot arm; aborting remaining cases\n");
      return 1;
    }

    char marker[64];
    int st = run_in_child(marker, sizeof(marker), body_detect_raw);
    report(check_detection(st, marker),
           "full: malloc on registered tid dies with SIGSEGV and emits the marker");

    st = run_in_child(marker, sizeof(marker), body_no_false_positive);
    report(child_exited_with(st, 0),
           "full: allocation on an unregistered tid never trips the detector");
    if (marker[0] != '\0') {
      unlink(marker);
    }

    st = run_in_child(marker, sizeof(marker), body_reset_disables);
    report(child_exited_with(st, 0),
           "full: set_sighandler_tid(-1) disarms the detector");
    if (marker[0] != '\0') {
      unlink(marker);
    }

    st = run_in_child(marker, sizeof(marker), body_detect_in_signal_handler);
    report(check_detection(st, marker),
           "full: malloc inside a real signal handler on the registered tid dies with SIGSEGV");

    st = run_in_child(marker, sizeof(marker), body_detect_via_shims);
    report(check_detection(st, marker),
           "full: Shims::setSighandlerTid (production wiring) arms the detector");

    int pass = 1;
    for (int i = 0; i < 100; i++) {
      void *p = alloc_and_check((size_t)(i + 1) * 128);
      if (p == NULL) {
        pass = 0;
        break;
      }
      free(p);
    }
    report(pass, "full: pass-through allocation on the unregistered main thread");
  }

  printf("%s: %d failure(s)\n", control ? "control" : "full", g_failures);
  return g_failures == 0 ? 0 : 1;
}
