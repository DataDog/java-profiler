/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "estimatorSupport.h"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __GLIBC__
#include <gnu/libc-version.h>
#endif

namespace {

// Reads a whole file; false when it cannot be opened or read.
bool readFile(const char *path, std::string &s) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return false;
    }
    char buf[4096];
    size_t n;
    s.clear();
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        s.append(buf, n);
    }
    fclose(f);
    return true;
}

bool fileExists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

// Value after "some avg10=" in a /proc/pressure record, else NA.
std::string readPsiAvg10(const char *path) {
    static const char needle[] = "some avg10=";
    std::string s;
    if (!readFile(path, s)) {
        return "NA";
    }
    size_t p = s.find(needle);
    if (p == std::string::npos) {
        return "NA";
    }
    p += strlen(needle);
    size_t e = p;
    while (e < s.size() && !isspace((unsigned char)s[e])) {
        e++;
    }
    return e == p ? "NA" : s.substr(p, e - p);
}

std::string readLoadavg1m() {
    std::string s;
    if (!readFile("/proc/loadavg", s)) {
        return "NA";
    }
    size_t e = s.find(' ');
    return (e == std::string::npos || e == 0) ? "NA" : s.substr(0, e);
}

// Value of the nr_throttled field of a cgroup cpu.stat file, else "".
std::string parseThrottled(const char *path) {
    static const char needle[] = "nr_throttled ";
    std::string s;
    if (!readFile(path, s)) {
        return "";
    }
    size_t p = s.find(needle);
    if (p == std::string::npos) {
        return "";
    }
    p += strlen(needle);
    size_t e = p;
    while (e < s.size() && isdigit((unsigned char)s[e])) {
        e++;
    }
    return e == p ? "" : s.substr(p, e - p);
}

// cgroup v2 is detected by the presence of cgroup.controllers, mirroring
// count_cpus; v1 falls back to the two legacy mount points.
std::string readNrThrottled() {
    if (fileExists("/sys/fs/cgroup/cgroup.controllers")) {
        std::string v = parseThrottled("/sys/fs/cgroup/cpu.stat");
        return v.empty() ? "NA" : v;
    }
    const char *v1Paths[] = {"/sys/fs/cgroup/cpu,cpuacct/cpu.stat", "/sys/fs/cgroup/cpu/cpu.stat"};
    for (const char *path : v1Paths) {
        std::string v = parseThrottled(path);
        if (!v.empty()) {
            return v;
        }
    }
    return "NA";
}

// State and ppid parsed from the text after the closing paren of the comm
// field, which also tolerates spaces inside comm.
bool readProcStatState(const std::string &pidPath, char &state, int &ppid) {
    std::string s;
    if (!readFile(pidPath.c_str(), s)) {
        return false;
    }
    size_t close = s.rfind(')');
    if (close == std::string::npos || close + 4 >= s.size()) {
        return false;
    }
    state = s[close + 2];
    ppid = atoi(s.c_str() + close + 4);
    return state != ' ';
}

// Runnable processes visible in /proc, excluding this process and its direct
// children; -1 when the census itself is unreadable.
int countRunnableCotenants() {
    int self = (int)getpid();
    DIR *d = opendir("/proc");
    if (d == NULL) {
        return -1;
    }
    int count = 0;
    struct dirent *de;
    while ((de = readdir(d)) != NULL) {
        if (!isdigit((unsigned char)de->d_name[0])) {
            continue;
        }
        int pid = atoi(de->d_name);
        if (pid == self) {
            continue;
        }
        char state;
        int ppid;
        if (!readProcStatState(std::string("/proc/") + de->d_name + "/stat", state, ppid)) {
            continue;
        }
        if (ppid == self) {
            continue;
        }
        if (state == 'R') {
            count++;
        }
    }
    closedir(d);
    return count;
}

// musl has no version API; the loader banner carries the version line. Any
// failure (no musl mapping, unreadable banner) means NA.
std::string probeMuslVersion() {
    std::string maps;
    if (!readFile("/proc/self/maps", maps)) {
        return "";
    }
    size_t p = maps.find("musl");
    if (p == std::string::npos) {
        return "";
    }
    size_t e = p;
    while (e < maps.size() && maps[e] != '\n') {
        e++;
    }
    size_t lineStart = maps.rfind('\n', p);
    lineStart = lineStart == std::string::npos ? 0 : lineStart + 1;
    size_t slash = maps.find('/', lineStart);
    if (slash == std::string::npos || slash >= e) {
        return "";
    }
    std::string cmd = maps.substr(slash, e - slash) + " 2>&1";
    FILE *f = popen(cmd.c_str(), "r");
    if (f == NULL) {
        return "";
    }
    std::string out;
    char buf[512];
    while (fgets(buf, sizeof(buf), f) != NULL) {
        out += buf;
    }
    pclose(f);
    size_t v = out.find("Version ");
    if (v == std::string::npos) {
        return "";
    }
    size_t vs = v + strlen("Version ");
    size_t ve = vs;
    while (ve < out.size() && out[ve] != '\n') {
        ve++;
    }
    return ve == vs ? "" : out.substr(vs, ve - vs);
}

const std::string &muslVersion() {
    static const std::string version = probeMuslVersion();
    return version;
}

} // namespace

std::string readMarkerRecord() {
    std::string psiCpu = readPsiAvg10("/proc/pressure/cpu");
    std::string psiMemory = readPsiAvg10("/proc/pressure/memory");
    std::string loadavg = readLoadavg1m();
    std::string throttled = readNrThrottled();
    int runnable = countRunnableCotenants();
    char runnableStr[16];
    if (runnable < 0) {
        strcpy(runnableStr, "NA");
    } else {
        snprintf(runnableStr, sizeof(runnableStr), "%d", runnable);
    }
    return "markers: psi_cpu_some_avg10=" + psiCpu + " psi_memory_some_avg10=" + psiMemory +
           " loadavg_1m=" + loadavg + " cpu_nr_throttled=" + throttled +
           " cotenant_runnable=" + runnableStr;
}

std::string libcName() {
#ifdef __GLIBC__
    return "glibc";
#else
    return muslVersion().empty() ? "NA" : "musl";
#endif
}

std::string libcVersion() {
#ifdef __GLIBC__
    return gnu_get_libc_version();
#else
    const std::string &version = muslVersion();
    return version.empty() ? "NA" : version;
#endif
}

uint64_t monotonicNanos() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}
