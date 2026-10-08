# Phase 0: memcheck noise

- profiler-commit: `adbd3fff8eccc3536f35fa87c4023378a9e281cc`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `4`
- runs: counters=50, nmt=50, noprof=15

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.020 | 0.000 | 2.34% | 0.020..0.021 | stable | 0.020 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.040 | 0.001 | 2.56% | 0.039..0.042 | stable | 0.040 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 2.48% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 24.965 | 0.010 | 0.04% | 24.954..24.981 | stable | 24.964 |
| `native_mem_live_bytes.calltrace` | 10 | 3.708 | 0.005 | 0.15% | 3.699..3.716 | stable | 3.708 |
| `native_mem_live_bytes.dictionary` | 10 | 6.801 | 0.003 | 0.04% | 6.797..6.803 | stable | 6.802 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.095 | 0.003 | 3.66% | 0.091..0.102 | stable | 0.096 |
| `native_mem_live_bytes.method_map` | 10 | 0.241 | 0.006 | 2.56% | 0.232..0.251 | stable | 0.238 |
| `native_mem_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.13% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 10 | 26.122 | 0.016 | 0.06% | 26.101..26.150 | stable | 26.118 |
| `native_mem_max_bytes.calltrace` | 10 | 4.863 | 0.008 | 0.16% | 4.853..4.878 | stable | 4.861 |
| `native_mem_max_bytes.dictionary` | 10 | 6.801 | 0.003 | 0.04% | 6.797..6.803 | stable | 6.802 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.095 | 0.003 | 3.66% | 0.091..0.102 | stable | 0.096 |
| `native_mem_max_bytes.method_map` | 10 | 0.241 | 0.006 | 2.56% | 0.232..0.251 | stable | 0.238 |
| `native_mem_max_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.84% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 10 | 24.965 | 0.010 | 0.04% | 24.954..24.981 | stable | 24.964 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.562 | 0.000 | 0.01% | 3.562..3.563 | stable | 3.562 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.049 | 0.006 | 0.09% | 6.041..6.053 | stable | 6.052 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.095 | 0.003 | 3.66% | 0.091..0.102 | stable | 0.096 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.241 | 0.006 | 2.56% | 0.232..0.251 | stable | 0.238 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.84% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.59% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 4.881 | 0.001 | 0.01% | stable | 4.523 | 0.358 |
| internal | 10 | 1.819 | 0.005 | 0.28% | stable | 1.463 | 0.356 |
| thread | 10 | 0.952 | 0.020 | 2.13% | stable | 0.957 | -0.006 |
| symbol | 10 | 1.594 | 0.001 | 0.03% | stable | 1.573 | 0.021 |
| code | 10 | 18.052 | 0.079 | 0.44% | stable | 16.842 | 1.210 |
| metaspace | 10 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 10 | 0.828 | 0.027 | 3.22% | stable | 0.663 | 0.165 |
| native_memory_tracking | 10 | 1.290 | 0.004 | 0.34% | stable | 1.089 | 0.201 |
| total | 10 | 618.380 | 0.131 | 0.02% | stable | 615.979 | 2.401 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 633.186 | 1.269 |
| counters | RssAnon | 10 | 606.633 | 1.315 |
| nmt | VmRSS | 10 | 634.615 | 0.829 |
| nmt | RssAnon | 10 | 608.018 | 0.789 |
| noprof | VmRSS | 3 | 603.504 | 0.734 |
| noprof | RssAnon | 3 | 581.001 | 0.789 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.056 | 0.000 | 0.34% | 0.056..0.057 | stable | 0.056 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.060 | 0.000 | 0.72% | 0.059..0.061 | stable | 0.060 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 4.02% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 25.861 | 0.014 | 0.05% | 25.839..25.881 | stable | 25.872 |
| `native_mem_live_bytes.calltrace` | 10 | 4.387 | 0.009 | 0.20% | 4.373..4.401 | stable | 4.395 |
| `native_mem_live_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.191 | 0.005 | 2.75% | 0.182..0.199 | stable | 0.193 |
| `native_mem_live_bytes.method_map` | 10 | 0.361 | 0.003 | 0.72% | 0.357..0.365 | stable | 0.362 |
| `native_mem_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 1.12% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 10 | 26.906 | 0.010 | 0.04% | 26.893..26.921 | stable | 26.910 |
| `native_mem_max_bytes.calltrace` | 10 | 5.423 | 0.004 | 0.07% | 5.418..5.430 | stable | 5.424 |
| `native_mem_max_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.191 | 0.005 | 2.75% | 0.182..0.199 | stable | 0.193 |
| `native_mem_max_bytes.method_map` | 10 | 0.361 | 0.003 | 0.72% | 0.357..0.365 | stable | 0.362 |
| `native_mem_max_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 25.861 | 0.014 | 0.05% | 25.839..25.881 | stable | 25.872 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.623 | 0.000 | 0.01% | 3.622..3.623 | stable | 3.623 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.191 | 0.005 | 2.75% | 0.182..0.199 | stable | 0.193 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.361 | 0.003 | 0.72% | 0.357..0.365 | stable | 0.362 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 68.398 | 0.001 | 0.00% | stable | 65.459 | 2.938 |
| internal | 10 | 6.346 | 0.005 | 0.07% | stable | 3.292 | 3.054 |
| thread | 10 | 0.936 | 0.002 | 0.24% | stable | 0.935 | 0.001 |
| symbol | 10 | 5.878 | 0.000 | 0.00% | stable | 5.857 | 0.021 |
| code | 10 | 56.358 | 0.274 | 0.49% | stable | 51.508 | 4.850 |
| metaspace | 10 | 114.975 | 0.378 | 0.33% | stable | 115.195 | -0.220 |
| arena_chunk | 10 | 1.873 | 0.227 | 12.14% | noisy | 1.312 | 0.562 |
| native_memory_tracking | 10 | 10.604 | 0.019 | 0.18% | stable | 8.607 | 1.997 |
| total | 10 | 848.099 | 0.305 | 0.04% | stable | 835.040 | 13.059 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 875.612 | 4.386 |
| counters | RssAnon | 10 | 848.945 | 4.459 |
| nmt | VmRSS | 10 | 885.614 | 4.227 |
| nmt | RssAnon | 10 | 858.940 | 4.243 |
| noprof | VmRSS | 3 | 849.203 | 2.482 |
| noprof | RssAnon | 3 | 826.663 | 2.492 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.080 | 0.001 | 0.93% | 0.079..0.081 | stable | 0.079 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.071 | 0.000 | 0.63% | 0.070..0.072 | stable | 0.071 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 2.70% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 26.432 | 0.010 | 0.04% | 26.421..26.449 | stable | 26.430 |
| `native_mem_live_bytes.calltrace` | 10 | 4.451 | 0.010 | 0.23% | 4.436..4.471 | stable | 4.452 |
| `native_mem_live_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.132 | 0.005 | 3.49% | 0.126..0.140 | stable | 0.130 |
| `native_mem_live_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 10 | 0.425 | 0.003 | 0.63% | 0.422..0.430 | stable | 0.424 |
| `native_mem_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.12% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 10 | 27.819 | 0.015 | 0.05% | 27.792..27.841 | stable | 27.809 |
| `native_mem_max_bytes.calltrace` | 10 | 5.828 | 0.010 | 0.17% | 5.807..5.841 | stable | 5.822 |
| `native_mem_max_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.132 | 0.005 | 3.49% | 0.126..0.140 | stable | 0.130 |
| `native_mem_max_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 10 | 0.425 | 0.003 | 0.63% | 0.422..0.430 | stable | 0.424 |
| `native_mem_max_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.003 | 0.000 | 3.60% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 10 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 26.432 | 0.010 | 0.04% | 26.421..26.449 | stable | 26.430 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.683 | 0.001 | 0.02% | 3.681..3.684 | stable | 3.682 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.132 | 0.005 | 3.49% | 0.126..0.140 | stable | 0.130 |
| `native_mem_post_flush_live_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.425 | 0.003 | 0.63% | 0.422..0.430 | stable | 0.424 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.003 | 0.000 | 3.60% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.66% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 4.882 | 0.001 | 0.02% | stable | 4.524 | 0.358 |
| internal | 10 | 1.856 | 0.004 | 0.23% | stable | 1.464 | 0.392 |
| thread | 10 | 0.957 | 0.018 | 1.84% | stable | 0.959 | -0.002 |
| symbol | 10 | 1.594 | 0.001 | 0.03% | stable | 1.573 | 0.021 |
| code | 10 | 17.993 | 0.101 | 0.56% | stable | 16.822 | 1.171 |
| metaspace | 10 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 10 | 0.840 | 0.010 | 1.19% | stable | 0.781 | 0.059 |
| native_memory_tracking | 10 | 1.297 | 0.004 | 0.29% | stable | 1.089 | 0.208 |
| total | 10 | 618.405 | 0.140 | 0.02% | stable | 615.965 | 2.440 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 635.684 | 2.041 |
| counters | RssAnon | 10 | 608.947 | 2.104 |
| nmt | VmRSS | 10 | 636.401 | 2.048 |
| nmt | RssAnon | 10 | 609.716 | 2.154 |
| noprof | VmRSS | 3 | 603.521 | 1.024 |
| noprof | RssAnon | 3 | 581.077 | 1.103 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.000 | 0.000 | 12.27% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.001 | 0.000 | 18.78% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.005 | 0.000 | 0.10% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 10 | 22.408 | 0.004 | 0.02% | 22.399..22.414 | stable | 22.410 |
| `native_mem_live_bytes.calltrace` | 10 | 3.544 | 0.000 | 0.01% | 3.543..3.544 | stable | 3.544 |
| `native_mem_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.007 | 0.003 | 49.42% | 0.001..0.012 | stable | 0.007 |
| `native_mem_live_bytes.method_map` | 10 | 0.006 | 0.001 | 18.85% | 0.004..0.009 | stable | 0.007 |
| `native_mem_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 10 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 10 | 23.440 | 0.010 | 0.04% | 23.423..23.460 | stable | 23.444 |
| `native_mem_max_bytes.calltrace` | 10 | 4.550 | 0.001 | 0.01% | 4.549..4.551 | stable | 4.549 |
| `native_mem_max_bytes.dictionary` | 10 | 4.571 | 0.006 | 0.14% | 4.562..4.583 | stable | 4.574 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.007 | 0.003 | 49.42% | 0.001..0.012 | stable | 0.007 |
| `native_mem_max_bytes.method_map` | 10 | 0.006 | 0.001 | 18.85% | 0.004..0.009 | stable | 0.007 |
| `native_mem_max_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 10 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 22.408 | 0.003 | 0.02% | 22.404..22.414 | stable | 22.410 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.542 | 0.000 | 0.00% | 3.542..3.542 | stable | 3.542 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.007 | 0.003 | 49.42% | 0.001..0.012 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.006 | 0.001 | 18.85% | 0.004..0.009 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 10 | 1.711 | 0.002 | 0.12% | stable | 1.558 | 0.154 |
| thread | 10 | 21.839 | 0.002 | 0.01% | stable | 21.831 | 0.008 |
| symbol | 10 | 1.133 | 0.000 | 0.00% | stable | 1.119 | 0.014 |
| code | 10 | 7.441 | 0.001 | 0.01% | stable | 7.434 | 0.007 |
| metaspace | 10 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 10 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 10 | 0.336 | 0.000 | 0.12% | stable | 0.292 | 0.043 |
| total | 10 | 610.773 | 0.083 | 0.01% | stable | 610.175 | 0.598 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 612.618 | 0.087 |
| counters | RssAnon | 10 | 586.255 | 0.056 |
| nmt | VmRSS | 10 | 613.058 | 0.114 |
| nmt | RssAnon | 10 | 586.673 | 0.059 |
| noprof | VmRSS | 3 | 588.835 | 0.189 |
| noprof | RssAnon | 3 | 567.210 | 0.190 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.051 | 0.000 | 0.84% | 0.050..0.051 | stable | 0.051 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.076 | 0.001 | 0.96% | 0.075..0.077 | stable | 0.076 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 1.71% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 23.545 | 0.010 | 0.04% | 23.532..23.562 | stable | 23.545 |
| `native_mem_live_bytes.calltrace` | 10 | 4.274 | 0.009 | 0.20% | 4.260..4.284 | stable | 4.272 |
| `native_mem_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.555 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.143 | 0.005 | 3.36% | 0.136..0.150 | stable | 0.143 |
| `native_mem_live_bytes.method_map` | 10 | 0.455 | 0.004 | 0.96% | 0.449..0.462 | stable | 0.454 |
| `native_mem_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.92% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 10 | 25.171 | 0.011 | 0.04% | 25.158..25.190 | stable | 25.172 |
| `native_mem_max_bytes.calltrace` | 10 | 5.348 | 0.006 | 0.10% | 5.341..5.355 | stable | 5.349 |
| `native_mem_max_bytes.dictionary` | 10 | 5.096 | 0.001 | 0.03% | 5.094..5.098 | stable | 5.097 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.143 | 0.005 | 3.36% | 0.136..0.150 | stable | 0.143 |
| `native_mem_max_bytes.method_map` | 10 | 0.455 | 0.004 | 0.96% | 0.449..0.462 | stable | 0.454 |
| `native_mem_max_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.99% | 0.002..0.003 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 23.545 | 0.010 | 0.04% | 23.532..23.562 | stable | 23.545 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.617 | 0.000 | 0.01% | 3.616..3.618 | stable | 3.617 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.554 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.143 | 0.005 | 3.36% | 0.136..0.150 | stable | 0.143 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.455 | 0.004 | 0.96% | 0.449..0.462 | stable | 0.454 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.99% | 0.002..0.003 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.72% | 0.054..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 8.709 | 0.000 | 0.00% | stable | 8.250 | 0.459 |
| internal | 10 | 2.222 | 0.005 | 0.23% | stable | 1.626 | 0.596 |
| thread | 10 | 0.975 | 0.004 | 0.38% | stable | 0.976 | -0.000 |
| symbol | 10 | 1.965 | 0.000 | 0.00% | stable | 1.944 | 0.021 |
| code | 10 | 26.912 | 0.401 | 1.49% | banded | 23.730 | 3.181 |
| metaspace | 10 | 22.017 | 0.003 | 0.01% | stable | 21.762 | 0.256 |
| arena_chunk | 10 | 1.126 | 0.321 | 28.46% | noisy | 1.217 | -0.091 |
| native_memory_tracking | 10 | 2.175 | 0.008 | 0.36% | stable | 1.877 | 0.297 |
| total | 10 | 644.296 | 0.428 | 0.07% | stable | 639.332 | 4.964 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 673.091 | 3.156 |
| counters | RssAnon | 10 | 646.388 | 3.124 |
| nmt | VmRSS | 10 | 674.310 | 3.192 |
| nmt | RssAnon | 10 | 647.589 | 3.253 |
| noprof | VmRSS | 3 | 644.260 | 1.971 |
| noprof | RssAnon | 3 | 621.616 | 2.030 |
