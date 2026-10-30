# Phase 0: memcheck noise

- profiler-commit: `34948dde4cac0fdb68d1e8077e1d66bd13242843`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS`
- cpus: `4`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.022 | 0.000 | 2.22% | 0.022..0.023 | stable | 0.022 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.044 | 0.001 | 2.53% | 0.043..0.045 | stable | 0.043 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.57% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.726 | 0.009 | 0.04% | 24.718..24.735 | stable | 24.729 |
| `native_mem_live_bytes.calltrace` | 3 | 3.716 | 0.011 | 0.30% | 3.703..3.722 | stable | 3.723 |
| `native_mem_live_bytes.dictionary` | 3 | 6.801 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.105 | 0.003 | 3.26% | 0.102..0.109 | stable | 0.103 |
| `native_mem_live_bytes.method_map` | 3 | 0.264 | 0.007 | 2.53% | 0.257..0.269 | stable | 0.260 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.06% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.905 | 0.012 | 0.05% | 25.891..25.913 | stable | 25.899 |
| `native_mem_max_bytes.calltrace` | 3 | 4.893 | 0.007 | 0.14% | 4.885..4.897 | stable | 4.891 |
| `native_mem_max_bytes.dictionary` | 3 | 6.801 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.105 | 0.003 | 3.26% | 0.102..0.109 | stable | 0.103 |
| `native_mem_max_bytes.method_map` | 3 | 0.264 | 0.007 | 2.53% | 0.257..0.269 | stable | 0.260 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.71% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.726 | 0.009 | 0.04% | 24.718..24.735 | stable | 24.729 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.568 | 0.001 | 0.01% | 3.567..3.568 | stable | 3.568 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.049 | 0.007 | 0.11% | 6.041..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.105 | 0.003 | 3.26% | 0.102..0.109 | stable | 0.103 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.264 | 0.007 | 2.53% | 0.257..0.269 | stable | 0.260 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.71% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.001 | 0.01% | stable | 4.528 | 0.295 |
| internal | 3 | 0.953 | 0.010 | 1.03% | stable | 0.587 | 0.366 |
| thread | 3 | 0.920 | 0.000 | 0.00% | stable | 0.919 | 0.001 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.600 | 0.038 | 0.20% | stable | 16.982 | 1.618 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.095 | 0.000 | 0.00% | stable | 0.001 | 0.094 |
| native_memory_tracking | 3 | 1.425 | 0.001 | 0.10% | stable | 1.222 | 0.203 |
| total | 3 | 617.704 | 0.044 | 0.01% | stable | 614.912 | 2.792 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 633.704 | 0.490 |
| counters | RssAnon | 3 | 606.954 | 0.553 |
| nmt | VmRSS | 3 | 635.809 | 0.748 |
| nmt | RssAnon | 3 | 609.148 | 0.678 |
| noprof | VmRSS | 1 | 604.723 | 0.000 |
| noprof | RssAnon | 1 | 582.391 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.107 | 0.002 | 1.57% | 0.105..0.108 | stable | 0.105 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.152 | 0.002 | 1.61% | 0.150..0.155 | stable | 0.150 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.12% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.299 | 0.015 | 0.06% | 26.282..26.310 | stable | 26.286 |
| `native_mem_live_bytes.calltrace` | 3 | 4.411 | 0.009 | 0.20% | 4.403..4.420 | stable | 4.411 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.329 | 0.004 | 1.12% | 0.327..0.334 | stable | 0.328 |
| `native_mem_live_bytes.method_map` | 3 | 0.914 | 0.015 | 1.60% | 0.901..0.930 | stable | 0.902 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.76% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.135 | 0.039 | 0.14% | 28.101..28.177 | stable | 28.115 |
| `native_mem_max_bytes.calltrace` | 3 | 6.239 | 0.021 | 0.33% | 6.221..6.262 | stable | 6.232 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.329 | 0.004 | 1.12% | 0.327..0.334 | stable | 0.328 |
| `native_mem_max_bytes.method_map` | 3 | 0.914 | 0.015 | 1.60% | 0.901..0.930 | stable | 0.902 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.76% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.299 | 0.015 | 0.06% | 26.282..26.310 | stable | 26.286 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.723 | 0.002 | 0.04% | 3.722..3.725 | stable | 3.722 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.329 | 0.004 | 1.12% | 0.327..0.334 | stable | 0.328 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.914 | 0.015 | 1.60% | 0.901..0.930 | stable | 0.902 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.86% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.401 | 0.001 | 0.00% | stable | 65.462 | 2.939 |
| internal | 3 | 6.728 | 0.008 | 0.12% | stable | 3.532 | 3.196 |
| thread | 3 | 0.934 | 0.002 | 0.24% | stable | 0.935 | -0.000 |
| symbol | 3 | 5.877 | 0.000 | 0.00% | stable | 5.856 | 0.021 |
| code | 3 | 59.196 | 0.494 | 0.83% | stable | 53.368 | 5.827 |
| metaspace | 3 | 117.320 | 1.405 | 1.20% | banded | 115.877 | 1.443 |
| arena_chunk | 3 | 0.702 | 0.001 | 0.08% | stable | 0.672 | 0.031 |
| native_memory_tracking | 3 | 12.086 | 0.060 | 0.50% | stable | 9.970 | 2.116 |
| total | 3 | 857.849 | 1.552 | 0.18% | stable | 842.287 | 15.562 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 875.013 | 2.884 |
| counters | RssAnon | 3 | 848.247 | 2.820 |
| nmt | VmRSS | 3 | 887.210 | 3.015 |
| nmt | RssAnon | 3 | 860.488 | 2.928 |
| noprof | VmRSS | 1 | 846.562 | 0.000 |
| noprof | RssAnon | 1 | 824.070 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 0.62% | 0.087..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.072 | 0.001 | 1.14% | 0.072..0.073 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.149 | 0.006 | 0.02% | 26.142..26.153 | stable | 26.167 |
| `native_mem_live_bytes.calltrace` | 3 | 4.434 | 0.006 | 0.13% | 4.428..4.440 | stable | 4.448 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.137 | 0.003 | 2.18% | 0.135..0.141 | stable | 0.134 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.434 | 0.005 | 1.12% | 0.430..0.439 | stable | 0.440 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.663 | 0.003 | 0.01% | 27.659..27.666 | stable | 27.668 |
| `native_mem_max_bytes.calltrace` | 3 | 5.937 | 0.011 | 0.19% | 5.925..5.947 | stable | 5.939 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.137 | 0.003 | 2.18% | 0.135..0.141 | stable | 0.134 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.434 | 0.005 | 1.12% | 0.430..0.439 | stable | 0.440 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 6.24% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.149 | 0.006 | 0.02% | 26.142..26.153 | stable | 26.167 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.02% | 3.693..3.694 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.137 | 0.003 | 2.18% | 0.135..0.141 | stable | 0.134 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.434 | 0.005 | 1.12% | 0.430..0.439 | stable | 0.440 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 6.24% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.056 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.001 | 0.01% | stable | 4.528 | 0.294 |
| internal | 3 | 0.987 | 0.003 | 0.30% | stable | 0.587 | 0.400 |
| thread | 3 | 0.921 | 0.002 | 0.24% | stable | 0.919 | 0.002 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.578 | 0.039 | 0.21% | stable | 16.915 | 1.663 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.105 | 0.018 | 17.16% | stable | 0.001 | 0.104 |
| native_memory_tracking | 3 | 1.433 | 0.001 | 0.08% | stable | 1.222 | 0.211 |
| total | 3 | 617.738 | 0.032 | 0.01% | stable | 614.845 | 2.894 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 635.828 | 0.070 |
| counters | RssAnon | 3 | 608.980 | 0.175 |
| nmt | VmRSS | 3 | 637.306 | 0.434 |
| nmt | RssAnon | 3 | 610.438 | 0.309 |
| noprof | VmRSS | 1 | 604.672 | 0.000 |
| noprof | RssAnon | 1 | 582.477 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 28.59% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 20.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.18% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.134 | 0.002 | 0.01% | 22.132..22.136 | stable | 22.134 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.007 | 0.001 | 10.13% | 0.006..0.008 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.001 | 19.30% | 0.006..0.008 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.28% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.164 | 0.003 | 0.01% | 23.162..23.168 | stable | 23.163 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.03% | 4.553..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.569 | 0.000 | 0.01% | 4.569..4.569 | stable | 4.567 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.007 | 0.001 | 10.13% | 0.006..0.008 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.001 | 19.30% | 0.006..0.008 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.134 | 0.002 | 0.01% | 22.132..22.136 | stable | 22.134 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.007 | 0.001 | 10.13% | 0.006..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.001 | 19.30% | 0.006..0.008 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 3 | 0.723 | 0.003 | 0.43% | stable | 0.565 | 0.158 |
| thread | 3 | 21.843 | 0.002 | 0.01% | stable | 21.837 | 0.006 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.121 | 0.013 |
| code | 3 | 7.440 | 0.001 | 0.02% | stable | 7.435 | 0.005 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.326 | 0.001 | 0.17% | stable | 0.282 | 0.044 |
| total | 3 | 609.955 | 0.015 | 0.00% | stable | 609.854 | 0.100 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 613.285 | 0.067 |
| counters | RssAnon | 3 | 586.914 | 0.058 |
| nmt | VmRSS | 3 | 613.878 | 0.221 |
| nmt | RssAnon | 3 | 587.332 | 0.329 |
| noprof | VmRSS | 1 | 589.543 | 0.000 |
| noprof | RssAnon | 1 | 567.949 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.054 | 0.000 | 0.14% | 0.054..0.054 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.079 | 0.000 | 0.58% | 0.079..0.080 | stable | 0.080 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.44% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.278 | 0.031 | 0.13% | 23.250..23.311 | stable | 23.287 |
| `native_mem_live_bytes.calltrace` | 3 | 4.261 | 0.034 | 0.80% | 4.230..4.297 | stable | 4.266 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.148 | 0.005 | 3.15% | 0.144..0.153 | stable | 0.148 |
| `native_mem_live_bytes.method_map` | 3 | 0.476 | 0.003 | 0.58% | 0.474..0.479 | stable | 0.480 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.81% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.967 | 0.008 | 0.03% | 24.958..24.972 | stable | 24.978 |
| `native_mem_max_bytes.calltrace` | 3 | 5.394 | 0.004 | 0.07% | 5.391..5.398 | stable | 5.402 |
| `native_mem_max_bytes.dictionary` | 3 | 5.099 | 0.003 | 0.07% | 5.096..5.102 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.148 | 0.005 | 3.15% | 0.144..0.153 | stable | 0.148 |
| `native_mem_max_bytes.method_map` | 3 | 0.476 | 0.003 | 0.58% | 0.474..0.479 | stable | 0.480 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.75% | 0.002..0.003 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.278 | 0.031 | 0.13% | 23.250..23.311 | stable | 23.287 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.000 | 0.00% | 3.624..3.624 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.148 | 0.005 | 3.15% | 0.144..0.153 | stable | 0.148 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.476 | 0.003 | 0.58% | 0.474..0.479 | stable | 0.480 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.75% | 0.002..0.003 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.000 | 0.00% | stable | 8.254 | 0.459 |
| internal | 3 | 1.384 | 0.001 | 0.07% | stable | 0.781 | 0.603 |
| thread | 3 | 0.967 | 0.005 | 0.47% | stable | 0.979 | -0.012 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 29.967 | 1.175 | 3.92% | banded | 26.645 | 3.322 |
| metaspace | 3 | 22.051 | 0.041 | 0.19% | stable | 21.762 | 0.289 |
| arena_chunk | 3 | 1.385 | 0.072 | 5.19% | noisy | 1.344 | 0.041 |
| native_memory_tracking | 3 | 2.379 | 0.022 | 0.95% | stable | 2.082 | 0.297 |
| total | 3 | 647.268 | 1.311 | 0.20% | stable | 642.251 | 5.017 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 673.206 | 2.062 |
| counters | RssAnon | 3 | 646.277 | 1.997 |
| nmt | VmRSS | 3 | 676.444 | 2.165 |
| nmt | RssAnon | 3 | 649.533 | 2.231 |
| noprof | VmRSS | 1 | 655.648 | 0.000 |
| noprof | RssAnon | 1 | 633.148 | 0.000 |
