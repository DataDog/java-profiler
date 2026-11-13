# Phase 0: memcheck noise

- profiler-commit: `adbd3fff8eccc3536f35fa87c4023378a9e281cc`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `2`
- runs: counters=15, nmt=15, noprof=15

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 0.41% | 0.021..0.021 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.041 | 0.000 | 0.27% | 0.041..0.041 | stable | 0.040 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.962 | 0.005 | 0.02% | 24.958..24.968 | stable | 24.955 |
| `native_mem_live_bytes.calltrace` | 3 | 3.698 | 0.006 | 0.16% | 3.695..3.705 | stable | 3.697 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.098 | 0.002 | 2.02% | 0.097..0.101 | stable | 0.094 |
| `native_mem_live_bytes.method_map` | 3 | 0.244 | 0.001 | 0.27% | 0.243..0.245 | stable | 0.242 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 26.132 | 0.003 | 0.01% | 26.131..26.135 | stable | 26.126 |
| `native_mem_max_bytes.calltrace` | 3 | 4.867 | 0.001 | 0.02% | 4.867..4.868 | stable | 4.868 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.098 | 0.002 | 2.02% | 0.097..0.101 | stable | 0.094 |
| `native_mem_max_bytes.method_map` | 3 | 0.244 | 0.001 | 0.27% | 0.243..0.245 | stable | 0.242 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_observed_total_bytes` | 3 | 24.962 | 0.005 | 0.02% | 24.958..24.968 | stable | 24.955 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.562 | 0.000 | 0.00% | 3.562..3.563 | stable | 3.563 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.098 | 0.002 | 2.02% | 0.097..0.101 | stable | 0.094 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.244 | 0.001 | 0.27% | 0.243..0.245 | stable | 0.242 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.880 | 0.000 | 0.00% | stable | 4.522 | 0.358 |
| internal | 3 | 1.813 | 0.003 | 0.14% | stable | 1.460 | 0.354 |
| thread | 3 | 0.888 | 0.000 | 0.00% | stable | 0.882 | 0.006 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.754 | 0.041 | 0.23% | stable | 16.704 | 1.050 |
| metaspace | 3 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.453 | 0.032 | 7.01% | stable | 0.326 | 0.126 |
| native_memory_tracking | 3 | 1.251 | 0.009 | 0.74% | stable | 1.051 | 0.200 |
| total | 3 | 613.435 | 0.092 | 0.02% | stable | 611.187 | 2.248 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 631.046 | 1.434 |
| counters | RssAnon | 3 | 604.400 | 1.326 |
| nmt | VmRSS | 3 | 631.310 | 0.727 |
| nmt | RssAnon | 3 | 604.665 | 0.787 |
| noprof | VmRSS | 3 | 603.076 | 0.289 |
| noprof | RssAnon | 3 | 580.526 | 0.261 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.000 | 0.25% | 0.056..0.056 | stable | 0.056 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.061 | 0.000 | 0.40% | 0.060..0.061 | stable | 0.060 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 5.56% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 25.877 | 0.009 | 0.03% | 25.867..25.885 | stable | 25.870 |
| `native_mem_live_bytes.calltrace` | 3 | 4.391 | 0.004 | 0.09% | 4.387..4.395 | stable | 4.393 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.200 | 0.004 | 1.85% | 0.196..0.203 | stable | 0.193 |
| `native_mem_live_bytes.method_map` | 3 | 0.364 | 0.001 | 0.40% | 0.362..0.365 | stable | 0.362 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 26.920 | 0.006 | 0.02% | 26.915..26.926 | stable | 26.909 |
| `native_mem_max_bytes.calltrace` | 3 | 5.425 | 0.005 | 0.08% | 5.421..5.430 | stable | 5.423 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.200 | 0.004 | 1.85% | 0.196..0.203 | stable | 0.193 |
| `native_mem_max_bytes.method_map` | 3 | 0.364 | 0.001 | 0.40% | 0.362..0.365 | stable | 0.362 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 25.877 | 0.009 | 0.03% | 25.867..25.885 | stable | 25.870 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.623 | 0.000 | 0.00% | 3.622..3.623 | stable | 3.622 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.200 | 0.004 | 1.85% | 0.196..0.203 | stable | 0.193 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.364 | 0.001 | 0.40% | 0.362..0.365 | stable | 0.362 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 66.929 | 2.540 | 3.80% | banded | 65.458 | 1.472 |
| internal | 3 | 6.170 | 0.164 | 2.66% | banded | 3.212 | 2.958 |
| thread | 3 | 0.902 | 0.002 | 0.25% | stable | 0.900 | 0.002 |
| symbol | 3 | 5.775 | 0.178 | 3.08% | banded | 5.857 | -0.082 |
| code | 3 | 49.921 | 1.078 | 2.16% | banded | 46.541 | 3.380 |
| metaspace | 3 | 110.701 | 3.765 | 3.40% | banded | 113.579 | -2.877 |
| arena_chunk | 3 | 1.385 | 1.145 | 82.66% | noisy | 1.826 | -0.441 |
| native_memory_tracking | 3 | 10.185 | 0.341 | 3.35% | banded | 8.411 | 1.773 |
| total | 3 | 830.334 | 9.196 | 1.11% | banded | 824.052 | 6.282 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 851.099 | 4.884 |
| counters | RssAnon | 3 | 824.358 | 4.903 |
| nmt | VmRSS | 3 | 854.458 | 19.036 |
| nmt | RssAnon | 3 | 827.777 | 19.067 |
| noprof | VmRSS | 3 | 828.930 | 2.335 |
| noprof | RssAnon | 3 | 806.333 | 2.325 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.084 | 0.001 | 0.94% | 0.083..0.085 | stable | 0.084 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.071 | 0.001 | 1.14% | 0.071..0.072 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 3.27% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.530 | 0.012 | 0.05% | 26.521..26.544 | stable | 26.544 |
| `native_mem_live_bytes.calltrace` | 3 | 4.545 | 0.009 | 0.20% | 4.534..4.550 | stable | 4.545 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.134 | 0.006 | 4.20% | 0.129..0.140 | stable | 0.140 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.429 | 0.005 | 1.14% | 0.423..0.432 | stable | 0.436 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.887 | 0.022 | 0.08% | 27.863..27.902 | stable | 27.903 |
| `native_mem_max_bytes.calltrace` | 3 | 5.893 | 0.013 | 0.22% | 5.879..5.902 | stable | 5.896 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.134 | 0.006 | 4.20% | 0.129..0.140 | stable | 0.140 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.429 | 0.005 | 1.14% | 0.423..0.432 | stable | 0.436 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.27% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.530 | 0.012 | 0.05% | 26.521..26.544 | stable | 26.544 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.687 | 0.001 | 0.04% | 3.686..3.688 | stable | 3.687 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.134 | 0.006 | 4.20% | 0.129..0.140 | stable | 0.140 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.429 | 0.005 | 1.14% | 0.423..0.432 | stable | 0.436 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.27% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.880 | 0.001 | 0.02% | stable | 4.522 | 0.358 |
| internal | 3 | 1.863 | 0.006 | 0.30% | stable | 1.460 | 0.403 |
| thread | 3 | 0.901 | 0.008 | 0.90% | stable | 0.882 | 0.019 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.901 | 0.146 | 0.82% | stable | 16.683 | 1.217 |
| metaspace | 3 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.432 | 0.018 | 4.24% | stable | 0.390 | 0.042 |
| native_memory_tracking | 3 | 1.265 | 0.006 | 0.47% | stable | 1.051 | 0.215 |
| total | 3 | 613.631 | 0.129 | 0.02% | stable | 611.189 | 2.442 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 631.917 | 0.624 |
| counters | RssAnon | 3 | 605.194 | 0.635 |
| nmt | VmRSS | 3 | 643.017 | 8.295 |
| nmt | RssAnon | 3 | 616.293 | 8.194 |
| noprof | VmRSS | 3 | 602.990 | 0.355 |
| noprof | RssAnon | 3 | 580.441 | 0.332 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 4.50% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 28.48% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.18% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.405 | 0.006 | 0.03% | 22.399..22.412 | stable | 22.410 |
| `native_mem_live_bytes.calltrace` | 3 | 3.543 | 0.000 | 0.01% | 3.543..3.544 | stable | 3.543 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.006 | 0.005 | 80.22% | 0.001..0.011 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.005 | 0.001 | 27.28% | 0.004..0.007 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.21% | 0.205..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.434 | 0.012 | 0.05% | 23.422..23.447 | stable | 23.439 |
| `native_mem_max_bytes.calltrace` | 3 | 4.550 | 0.000 | 0.01% | 4.550..4.550 | stable | 4.549 |
| `native_mem_max_bytes.dictionary` | 3 | 4.566 | 0.006 | 0.13% | 4.562..4.573 | stable | 4.569 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.006 | 0.005 | 80.22% | 0.001..0.011 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.005 | 0.001 | 27.28% | 0.004..0.007 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.21% | 0.206..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.407 | 0.004 | 0.02% | 22.404..22.412 | stable | 22.410 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.542 | 0.000 | 0.00% | 3.542..3.542 | stable | 3.542 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.006 | 0.005 | 80.22% | 0.001..0.011 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.005 | 0.001 | 27.28% | 0.004..0.007 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.21% | 0.206..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.112 |
| internal | 3 | 1.711 | 0.003 | 0.15% | stable | 1.557 | 0.154 |
| thread | 3 | 21.815 | 0.000 | 0.00% | stable | 21.807 | 0.009 |
| symbol | 3 | 1.133 | 0.000 | 0.00% | stable | 1.119 | 0.014 |
| code | 3 | 7.440 | 0.001 | 0.02% | stable | 7.434 | 0.006 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.132 | 0.000 | 0.00% | stable | 0.132 | 0.000 |
| native_memory_tracking | 3 | 0.336 | 0.001 | 0.17% | stable | 0.292 | 0.044 |
| total | 3 | 606.934 | 0.112 | 0.02% | stable | 606.248 | 0.687 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 612.516 | 0.148 |
| counters | RssAnon | 3 | 586.221 | 0.130 |
| nmt | VmRSS | 3 | 613.026 | 0.059 |
| nmt | RssAnon | 3 | 586.680 | 0.086 |
| noprof | VmRSS | 3 | 588.945 | 0.070 |
| noprof | RssAnon | 3 | 567.310 | 0.086 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.050 | 0.000 | 0.34% | 0.050..0.050 | stable | 0.051 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.001 | 1.52% | 0.074..0.076 | stable | 0.075 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.534 | 0.028 | 0.12% | 23.503..23.555 | stable | 23.528 |
| `native_mem_live_bytes.calltrace` | 3 | 4.271 | 0.019 | 0.44% | 4.249..4.282 | stable | 4.262 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.142 | 0.005 | 3.31% | 0.138..0.147 | stable | 0.142 |
| `native_mem_live_bytes.method_map` | 3 | 0.450 | 0.007 | 1.52% | 0.442..0.454 | stable | 0.452 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.164 | 0.012 | 0.05% | 25.153..25.177 | stable | 25.176 |
| `native_mem_max_bytes.calltrace` | 3 | 5.349 | 0.002 | 0.05% | 5.347..5.351 | stable | 5.356 |
| `native_mem_max_bytes.dictionary` | 3 | 5.096 | 0.001 | 0.03% | 5.095..5.098 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.142 | 0.005 | 3.31% | 0.138..0.147 | stable | 0.142 |
| `native_mem_max_bytes.method_map` | 3 | 0.450 | 0.007 | 1.52% | 0.442..0.454 | stable | 0.452 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.534 | 0.028 | 0.12% | 23.503..23.555 | stable | 23.528 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.617 | 0.000 | 0.00% | 3.616..3.617 | stable | 3.617 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.142 | 0.005 | 3.31% | 0.138..0.147 | stable | 0.142 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.450 | 0.007 | 1.52% | 0.442..0.454 | stable | 0.452 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.710 | 0.001 | 0.01% | stable | 8.250 | 0.460 |
| internal | 3 | 2.235 | 0.002 | 0.09% | stable | 1.631 | 0.604 |
| thread | 3 | 0.903 | 0.000 | 0.00% | stable | 0.893 | 0.010 |
| symbol | 3 | 1.965 | 0.000 | 0.00% | stable | 1.944 | 0.021 |
| code | 3 | 29.671 | 0.646 | 2.18% | banded | 24.270 | 5.401 |
| metaspace | 3 | 21.954 | 0.000 | 0.00% | stable | 21.762 | 0.192 |
| arena_chunk | 3 | 0.371 | 0.144 | 38.90% | noisy | 0.595 | -0.224 |
| native_memory_tracking | 3 | 2.311 | 0.020 | 0.85% | stable | 1.939 | 0.371 |
| total | 3 | 642.631 | 0.612 | 0.10% | stable | 635.595 | 7.035 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 661.841 | 1.915 |
| counters | RssAnon | 3 | 635.074 | 1.878 |
| nmt | VmRSS | 3 | 665.504 | 1.240 |
| nmt | RssAnon | 3 | 638.733 | 1.278 |
| noprof | VmRSS | 3 | 631.803 | 3.143 |
| noprof | RssAnon | 3 | 609.118 | 3.073 |
