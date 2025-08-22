// macOS stub implementation for otel_process_ctx
// The OpenTelemetry process context specification is Linux-only

#ifdef __APPLE__

#include "otel_process_ctx.h"

otel_process_ctx_result otel_process_ctx_publish(otel_process_ctx_data data) {
  return (otel_process_ctx_result) {
    .success = false,
    .error_message = "OpenTelemetry process context is not supported on macOS"
  };
}

otel_process_ctx_result otel_process_ctx_update(otel_process_ctx_result *previous, otel_process_ctx_data data) {
  return (otel_process_ctx_result) {
    .success = false,
    .error_message = "OpenTelemetry process context is not supported on macOS"
  };
}

bool otel_process_ctx_drop(otel_process_ctx_result *previous) {
  // Always return true for no-op on macOS
  if (previous) {
    previous->success = false;
    previous->error_message = "Context dropped (macOS stub)";
    previous->published_context = nullptr;
  }
  return true;
}

#ifndef OTEL_PROCESS_CTX_NO_READ
otel_process_ctx_read_result otel_process_ctx_read(void) {
  return (otel_process_ctx_read_result) {
    .success = false,
    .error_message = "OpenTelemetry process context reading is not supported on macOS"
  };
}
#endif // OTEL_PROCESS_CTX_NO_READ

#endif // __APPLE__