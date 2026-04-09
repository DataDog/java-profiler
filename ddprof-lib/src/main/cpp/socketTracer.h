/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SOCKETTRACER_H
#define _SOCKETTRACER_H

#include "codeCache.h"
#include "spinLock.h"

#ifdef __linux__

/**
 * Operation name constants used as the {@code operation} field in SocketIOEvent.
 * These are string literals — no allocation needed in hot paths.
 * Declared inline to avoid duplicate definitions when the header is included
 * from multiple translation units (C++17).
 */
inline constexpr const char* SOCKET_OP_READ      = "read";
inline constexpr const char* SOCKET_OP_WRITE      = "write";
inline constexpr const char* SOCKET_OP_READV      = "readv";
inline constexpr const char* SOCKET_OP_WRITEV     = "writev";
inline constexpr const char* SOCKET_OP_RECV      = "recv";
inline constexpr const char* SOCKET_OP_SEND      = "send";
inline constexpr const char* SOCKET_OP_RECVMSG   = "recvmsg";
inline constexpr const char* SOCKET_OP_SENDMSG   = "sendmsg";
inline constexpr const char* SOCKET_OP_CONNECT    = "connect";
inline constexpr const char* SOCKET_OP_ACCEPT     = "accept";
inline constexpr const char* SOCKET_OP_ACCEPT4    = "accept4";
inline constexpr const char* SOCKET_OP_EPOLL_WAIT = "epoll_wait";

/**
 * Intercepts socket I/O calls in Netty's native transport library via PLT patching
 * and emits datadog.SocketIO JFR events for each intercepted operation.
 *
 * Only libraries whose base name contains "netty" are patched to avoid
 * excessive overhead from instrumenting unrelated I/O.
 */
class SocketTracer {
private:
  static SpinLock _lock;
  static bool _initialized;

  struct PatchedLib {
    CodeCache* lib;
    void* original_read;
    void* original_write;
    void* original_readv;
    void* original_writev;
    void* original_recv;
    void* original_send;
    void* original_recvmsg;
    void* original_sendmsg;
    void* original_connect;
    void* original_accept;
    void* original_accept4;
    void* original_epoll_wait;
  };

  static const int MAX_PATCHED_LIBS = 16;
  static PatchedLib _patched_libs[MAX_PATCHED_LIBS];
  static int _patched_count;

  static void patchLibraryUnlocked(CodeCache* lib);

public:
  static void initialize();
  static void patchLibraries();
  static void unpatchLibraries();
  static bool isInitialized() { return _initialized; }

  /** Returns true if the library name suggests it is a Netty native transport library. */
  static bool isNettyLibrary(const char* name);
};

#else

class SocketTracer {
public:
  static void initialize() {}
  static void patchLibraries() {}
  static void unpatchLibraries() {}
  static bool isInitialized() { return false; }
  static bool isNettyLibrary(const char*) { return false; }
};

#endif  // __linux__

#endif  // _SOCKETTRACER_H
