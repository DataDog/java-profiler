# Phase 0: memcheck noise

- profiler-commit: `adbd3fff8eccc3536f35fa87c4023378a9e281cc`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `8`
- runs: counters=15, nmt=15, noprof=15

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 0.79% | 0.021..0.021 | stable | 0.020 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.041 | 0.000 | 1.03% | 0.040..0.041 | stable | 0.040 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.977 | 0.008 | 0.03% | 24.968..24.982 | stable | 24.970 |
| `native_mem_live_bytes.calltrace` | 3 | 3.712 | 0.005 | 0.13% | 3.707..3.717 | stable | 3.713 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.097 | 0.001 | 1.07% | 0.096..0.098 | stable | 0.095 |
| `native_mem_live_bytes.method_map` | 3 | 0.245 | 0.003 | 1.03% | 0.242..0.247 | stable | 0.239 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.20% | 0.002..0.003 | stable | 0.003 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 26.136 | 0.006 | 0.02% | 26.129..26.140 | stable | 26.121 |
| `native_mem_max_bytes.calltrace` | 3 | 4.868 | 0.003 | 0.07% | 4.865..4.871 | stable | 4.862 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.097 | 0.001 | 1.07% | 0.096..0.098 | stable | 0.095 |
| `native_mem_max_bytes.method_map` | 3 | 0.245 | 0.003 | 1.03% | 0.242..0.247 | stable | 0.239 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 1.32% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_observed_total_bytes` | 3 | 24.977 | 0.008 | 0.03% | 24.968..24.982 | stable | 24.970 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.563 | 0.000 | 0.00% | 3.562..3.563 | stable | 3.562 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.097 | 0.001 | 1.07% | 0.096..0.098 | stable | 0.095 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.245 | 0.003 | 1.03% | 0.242..0.247 | stable | 0.239 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 1.32% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.056 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.883 | 0.001 | 0.02% | stable | 4.525 | 0.357 |
| internal | 3 | 1.823 | 0.004 | 0.25% | stable | 1.469 | 0.354 |
| thread | 3 | 1.068 | 0.002 | 0.21% | stable | 1.064 | 0.004 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.733 | 0.037 | 0.20% | stable | 17.174 | 1.559 |
| metaspace | 3 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.833 | 0.639 | 76.75% | noisy | 0.471 | 0.362 |
| native_memory_tracking | 3 | 1.317 | 0.001 | 0.11% | stable | 1.116 | 0.201 |
| total | 3 | 627.401 | 0.608 | 0.10% | stable | 624.621 | 2.780 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 636.021 | 1.108 |
| counters | RssAnon | 3 | 609.393 | 1.061 |
| nmt | VmRSS | 3 | 637.773 | 0.388 |
| nmt | RssAnon | 3 | 611.176 | 0.387 |
| noprof | VmRSS | 3 | 605.651 | 1.254 |
| noprof | RssAnon | 3 | 583.315 | 1.226 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.000 | 0.46% | 0.056..0.057 | stable | 0.056 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.061 | 0.000 | 0.47% | 0.060..0.061 | stable | 0.060 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 25.877 | 0.018 | 0.07% | 25.863..25.898 | stable | 25.868 |
| `native_mem_live_bytes.calltrace` | 3 | 4.395 | 0.016 | 0.35% | 4.382..4.412 | stable | 4.389 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.196 | 0.001 | 0.75% | 0.194..0.197 | stable | 0.193 |
| `native_mem_live_bytes.method_map` | 3 | 0.363 | 0.002 | 0.47% | 0.362..0.365 | stable | 0.362 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 26.917 | 0.008 | 0.03% | 26.911..26.926 | stable | 26.908 |
| `native_mem_max_bytes.calltrace` | 3 | 5.425 | 0.005 | 0.09% | 5.421..5.431 | stable | 5.421 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.196 | 0.001 | 0.75% | 0.194..0.197 | stable | 0.193 |
| `native_mem_max_bytes.method_map` | 3 | 0.363 | 0.002 | 0.47% | 0.362..0.365 | stable | 0.362 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.65% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 25.877 | 0.018 | 0.07% | 25.863..25.898 | stable | 25.868 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.623 | 0.000 | 0.01% | 3.622..3.623 | stable | 3.622 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.196 | 0.001 | 0.75% | 0.194..0.197 | stable | 0.193 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.363 | 0.002 | 0.47% | 0.362..0.365 | stable | 0.362 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.65% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.460 | 2.939 |
| internal | 3 | 6.358 | 0.001 | 0.02% | stable | 3.301 | 3.056 |
| thread | 3 | 1.028 | 0.002 | 0.22% | stable | 1.021 | 0.007 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 56.964 | 0.102 | 0.18% | stable | 51.924 | 5.039 |
| metaspace | 3 | 115.339 | 0.492 | 0.43% | stable | 115.758 | -0.419 |
| arena_chunk | 3 | 2.004 | 0.019 | 0.96% | stable | 0.714 | 1.290 |
| native_memory_tracking | 3 | 10.635 | 0.022 | 0.20% | stable | 8.643 | 1.993 |
| total | 3 | 857.539 | 0.523 | 0.06% | stable | 843.418 | 14.121 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 883.525 | 6.226 |
| counters | RssAnon | 3 | 856.896 | 6.167 |
| nmt | VmRSS | 3 | 890.327 | 2.007 |
| nmt | RssAnon | 3 | 863.661 | 2.102 |
| noprof | VmRSS | 3 | 856.617 | 4.968 |
| noprof | RssAnon | 3 | 834.111 | 4.958 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.079 | 0.001 | 0.85% | 0.078..0.079 | stable | 0.079 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.071 | 0.001 | 0.89% | 0.070..0.072 | stable | 0.071 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.385 | 0.006 | 0.02% | 26.381..26.391 | stable | 26.389 |
| `native_mem_live_bytes.calltrace` | 3 | 4.400 | 0.003 | 0.08% | 4.397..4.403 | stable | 4.405 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.136 | 0.006 | 4.25% | 0.132..0.142 | stable | 0.133 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.426 | 0.004 | 0.89% | 0.422..0.429 | stable | 0.427 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.003 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.807 | 0.014 | 0.05% | 27.792..27.815 | stable | 27.813 |
| `native_mem_max_bytes.calltrace` | 3 | 5.811 | 0.008 | 0.15% | 5.802..5.819 | stable | 5.818 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.01% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.136 | 0.006 | 4.25% | 0.132..0.142 | stable | 0.133 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.426 | 0.004 | 0.89% | 0.422..0.429 | stable | 0.427 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.004 | 0.000 | 3.84% | 0.004..0.004 | stable | 0.004 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.385 | 0.006 | 0.02% | 26.381..26.391 | stable | 26.389 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.681 | 0.000 | 0.01% | 3.681..3.682 | stable | 3.681 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.136 | 0.006 | 4.25% | 0.132..0.142 | stable | 0.133 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.426 | 0.004 | 0.89% | 0.422..0.429 | stable | 0.427 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.004 | 0.000 | 3.84% | 0.004..0.004 | stable | 0.004 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.78% | 0.056..0.056 | stable | 0.056 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.883 | 0.001 | 0.01% | stable | 4.525 | 0.358 |
| internal | 3 | 1.864 | 0.008 | 0.45% | stable | 1.469 | 0.396 |
| thread | 3 | 1.079 | 0.002 | 0.21% | stable | 1.065 | 0.014 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.775 | 0.037 | 0.20% | stable | 17.220 | 1.555 |
| metaspace | 3 | 11.454 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.453 | 0.621 | 137.00% | noisy | 0.380 | 0.073 |
| native_memory_tracking | 3 | 1.326 | 0.001 | 0.07% | stable | 1.115 | 0.211 |
| total | 3 | 627.103 | 0.664 | 0.11% | stable | 624.289 | 2.813 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 636.105 | 1.453 |
| counters | RssAnon | 3 | 609.475 | 1.508 |
| nmt | VmRSS | 3 | 639.794 | 1.264 |
| nmt | RssAnon | 3 | 612.996 | 1.205 |
| noprof | VmRSS | 3 | 611.861 | 9.762 |
| noprof | RssAnon | 3 | 589.443 | 9.630 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 8.44% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 8.99% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.00% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.410 | 0.002 | 0.01% | 22.409..22.413 | stable | 22.411 |
| `native_mem_live_bytes.calltrace` | 3 | 3.544 | 0.001 | 0.01% | 3.544..3.545 | stable | 3.544 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.008 | 0.002 | 26.14% | 0.006..0.010 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.008 | 0.001 | 8.54% | 0.007..0.008 | stable | 0.008 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.029 | 0.000 | 0.00% | 0.029..0.029 | stable | 0.029 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.455 | 0.007 | 0.03% | 23.447..23.461 | stable | 23.451 |
| `native_mem_max_bytes.calltrace` | 3 | 4.550 | 0.000 | 0.01% | 4.550..4.550 | stable | 4.550 |
| `native_mem_max_bytes.dictionary` | 3 | 4.582 | 0.005 | 0.11% | 4.577..4.586 | stable | 4.579 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.008 | 0.002 | 26.14% | 0.006..0.010 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.008 | 0.001 | 8.54% | 0.007..0.008 | stable | 0.008 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.029 | 0.000 | 0.00% | 0.029..0.029 | stable | 0.029 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.410 | 0.002 | 0.01% | 22.409..22.413 | stable | 22.411 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.542 | 0.000 | 0.00% | 3.542..3.542 | stable | 3.542 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.008 | 0.002 | 26.14% | 0.006..0.010 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.008 | 0.001 | 8.54% | 0.007..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.029 | 0.000 | 0.00% | 0.029..0.029 | stable | 0.029 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.384 | 0.000 | 0.00% | stable | 0.272 | 0.111 |
| internal | 3 | 1.715 | 0.001 | 0.03% | stable | 1.562 | 0.154 |
| thread | 3 | 21.880 | 0.002 | 0.01% | stable | 21.873 | 0.006 |
| symbol | 3 | 1.133 | 0.000 | 0.00% | stable | 1.119 | 0.014 |
| code | 3 | 7.441 | 0.000 | 0.00% | stable | 7.435 | 0.007 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.338 | 0.001 | 0.17% | stable | 0.294 | 0.043 |
| total | 3 | 618.936 | 0.087 | 0.01% | stable | 618.325 | 0.610 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 612.893 | 0.097 |
| counters | RssAnon | 3 | 586.499 | 0.063 |
| nmt | VmRSS | 3 | 613.184 | 0.051 |
| nmt | RssAnon | 3 | 586.866 | 0.045 |
| noprof | VmRSS | 3 | 588.935 | 0.101 |
| noprof | RssAnon | 3 | 567.339 | 0.050 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.050 | 0.000 | 0.12% | 0.050..0.050 | stable | 0.051 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.001 | 0.78% | 0.075..0.076 | stable | 0.076 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.42% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.520 | 0.009 | 0.04% | 23.510..23.525 | stable | 23.530 |
| `native_mem_live_bytes.calltrace` | 3 | 4.254 | 0.002 | 0.04% | 4.252..4.256 | stable | 4.257 |
| `native_mem_live_bytes.dictionary` | 3 | 4.559 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.137 | 0.006 | 4.49% | 0.131..0.144 | stable | 0.146 |
| `native_mem_live_bytes.method_map` | 3 | 0.449 | 0.004 | 0.78% | 0.447..0.453 | stable | 0.453 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 2.96% | 0.003..0.003 | stable | 0.003 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 25.162 | 0.010 | 0.04% | 25.152..25.171 | stable | 25.180 |
| `native_mem_max_bytes.calltrace` | 3 | 5.344 | 0.002 | 0.04% | 5.341..5.346 | stable | 5.352 |
| `native_mem_max_bytes.dictionary` | 3 | 5.101 | 0.008 | 0.16% | 5.095..5.110 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.137 | 0.006 | 4.49% | 0.131..0.144 | stable | 0.146 |
| `native_mem_max_bytes.method_map` | 3 | 0.449 | 0.004 | 0.78% | 0.447..0.453 | stable | 0.453 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 2.37% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.520 | 0.009 | 0.04% | 23.510..23.525 | stable | 23.530 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.617 | 0.000 | 0.00% | 3.617..3.617 | stable | 3.617 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.557 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.137 | 0.006 | 4.49% | 0.131..0.144 | stable | 0.146 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.449 | 0.004 | 0.78% | 0.447..0.453 | stable | 0.453 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 2.37% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.711 | 0.000 | 0.00% | stable | 8.251 | 0.460 |
| internal | 3 | 2.235 | 0.007 | 0.30% | stable | 1.635 | 0.600 |
| thread | 3 | 1.108 | 0.000 | 0.00% | stable | 1.051 | 0.058 |
| symbol | 3 | 1.965 | 0.000 | 0.00% | stable | 1.944 | 0.021 |
| code | 3 | 30.818 | 0.126 | 0.41% | stable | 27.319 | 3.499 |
| metaspace | 3 | 22.028 | 0.005 | 0.02% | stable | 21.800 | 0.228 |
| arena_chunk | 3 | 1.707 | 0.268 | 15.69% | noisy | 1.431 | 0.276 |
| native_memory_tracking | 3 | 2.247 | 0.004 | 0.18% | stable | 1.959 | 0.288 |
| total | 3 | 657.397 | 0.298 | 0.05% | stable | 651.758 | 5.639 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 688.423 | 4.741 |
| counters | RssAnon | 3 | 661.776 | 4.628 |
| nmt | VmRSS | 3 | 688.189 | 4.855 |
| nmt | RssAnon | 3 | 661.435 | 4.805 |
| noprof | VmRSS | 3 | 649.736 | 3.632 |
| noprof | RssAnon | 3 | 627.251 | 3.495 |
