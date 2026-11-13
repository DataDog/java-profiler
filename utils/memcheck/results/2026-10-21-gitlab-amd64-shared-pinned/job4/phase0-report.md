# Phase 0: memcheck noise

- profiler-commit: `3e6e73950647b25854993dfbe20e2b5ba51e4f81`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS`
- cpus: `4`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.022 | 0.001 | 2.60% | 0.021..0.022 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.042 | 0.001 | 2.58% | 0.041..0.043 | stable | 0.042 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 14.92% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.705 | 0.009 | 0.04% | 24.694..24.710 | stable | 24.704 |
| `native_mem_live_bytes.calltrace` | 3 | 3.714 | 0.007 | 0.18% | 3.708..3.721 | stable | 3.713 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.096 | 0.004 | 3.74% | 0.092..0.099 | stable | 0.096 |
| `native_mem_live_bytes.method_map` | 3 | 0.252 | 0.007 | 2.58% | 0.247..0.260 | stable | 0.251 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 23.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.876 | 0.020 | 0.08% | 25.858..25.898 | stable | 25.873 |
| `native_mem_max_bytes.calltrace` | 3 | 4.884 | 0.009 | 0.19% | 4.876..4.894 | stable | 4.882 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.096 | 0.004 | 3.74% | 0.092..0.099 | stable | 0.096 |
| `native_mem_max_bytes.method_map` | 3 | 0.252 | 0.007 | 2.58% | 0.247..0.260 | stable | 0.251 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.001 | 34.09% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_max_observed_total_bytes` | 3 | 24.705 | 0.009 | 0.04% | 24.694..24.710 | stable | 24.704 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.001 | 0.02% | 3.567..3.568 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.096 | 0.004 | 3.74% | 0.092..0.099 | stable | 0.096 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.252 | 0.007 | 2.58% | 0.247..0.260 | stable | 0.251 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.001 | 34.09% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.820 | 0.002 | 0.04% | stable | 4.528 | 0.291 |
| internal | 3 | 0.890 | 0.046 | 5.21% | stable | 0.587 | 0.303 |
| thread | 3 | 0.845 | 0.068 | 8.09% | noisy | 0.919 | -0.074 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.990 | 0.504 | 2.80% | banded | 16.913 | 1.076 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.334 | 0.209 | 62.72% | noisy | 0.001 | 0.333 |
| native_memory_tracking | 3 | 1.235 | 0.163 | 13.21% | noisy | 1.220 | 0.016 |
| total | 3 | 583.297 | 29.756 | 5.10% | noisy | 614.833 | -31.536 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 623.521 | 9.202 |
| counters | RssAnon | 3 | 597.703 | 8.491 |
| nmt | VmRSS | 3 | 629.992 | 8.962 |
| nmt | RssAnon | 3 | 604.258 | 8.540 |
| noprof | VmRSS | 1 | 603.887 | 0.000 |
| noprof | RssAnon | 1 | 581.340 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.114 | 0.010 | 9.05% | 0.105..0.125 | stable | 0.114 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.160 | 0.009 | 5.63% | 0.153..0.170 | stable | 0.158 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 24.74% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.368 | 0.068 | 0.26% | 26.324..26.446 | stable | 26.360 |
| `native_mem_live_bytes.calltrace` | 3 | 4.415 | 0.018 | 0.42% | 4.400..4.435 | stable | 4.422 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.352 | 0.029 | 8.20% | 0.328..0.384 | stable | 0.349 |
| `native_mem_live_bytes.method_map` | 3 | 0.958 | 0.054 | 5.64% | 0.916..1.019 | stable | 0.946 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 29.60% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.82% | 0.053..0.054 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 28.350 | 0.281 | 0.99% | 28.133..28.667 | stable | 28.371 |
| `native_mem_max_bytes.calltrace` | 3 | 6.389 | 0.198 | 3.10% | 6.237..6.613 | banded | 6.425 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.352 | 0.029 | 8.20% | 0.328..0.384 | stable | 0.349 |
| `native_mem_max_bytes.method_map` | 3 | 0.958 | 0.054 | 5.64% | 0.916..1.019 | stable | 0.946 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 23.34% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.368 | 0.068 | 0.26% | 26.324..26.446 | stable | 26.360 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.730 | 0.010 | 0.28% | 3.722..3.742 | stable | 3.730 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.352 | 0.029 | 8.20% | 0.328..0.384 | stable | 0.349 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.958 | 0.054 | 5.64% | 0.916..1.019 | stable | 0.946 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 23.34% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.462 | 2.937 |
| internal | 3 | 6.699 | 0.031 | 0.46% | stable | 3.529 | 3.169 |
| thread | 3 | 0.848 | 0.076 | 8.98% | noisy | 0.938 | -0.091 |
| symbol | 3 | 5.877 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 57.981 | 0.751 | 1.30% | banded | 52.365 | 5.616 |
| metaspace | 3 | 115.060 | 1.005 | 0.87% | stable | 118.670 | -3.610 |
| arena_chunk | 3 | 0.500 | 0.325 | 65.01% | noisy | 0.480 | 0.019 |
| native_memory_tracking | 3 | 11.499 | 0.469 | 4.08% | banded | 10.077 | 1.422 |
| total | 3 | 819.008 | 32.514 | 3.97% | banded | 844.127 | -25.119 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 866.415 | 8.490 |
| counters | RssAnon | 3 | 840.243 | 7.749 |
| nmt | VmRSS | 3 | 875.591 | 9.840 |
| nmt | RssAnon | 3 | 849.478 | 9.303 |
| noprof | VmRSS | 1 | 851.754 | 0.000 |
| noprof | RssAnon | 1 | 829.469 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.089 | 0.001 | 0.91% | 0.088..0.090 | stable | 0.090 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.074 | 0.001 | 1.23% | 0.073..0.075 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 13.29% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.355 | 0.024 | 0.09% | 26.334..26.381 | stable | 26.362 |
| `native_mem_live_bytes.calltrace` | 3 | 4.634 | 0.022 | 0.48% | 4.616..4.659 | stable | 4.651 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.146 | 0.002 | 1.51% | 0.144..0.148 | stable | 0.144 |
| `native_mem_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.483 |
| `native_mem_live_bytes.method_map` | 3 | 0.443 | 0.005 | 1.23% | 0.437..0.448 | stable | 0.441 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 20.93% | 0.001..0.002 | stable | 0.001 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.713 | 0.009 | 0.03% | 27.704..27.720 | stable | 27.710 |
| `native_mem_max_bytes.calltrace` | 3 | 5.983 | 0.011 | 0.18% | 5.971..5.990 | stable | 5.991 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.146 | 0.002 | 1.51% | 0.144..0.148 | stable | 0.144 |
| `native_mem_max_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.483 |
| `native_mem_max_bytes.method_map` | 3 | 0.443 | 0.005 | 1.23% | 0.437..0.448 | stable | 0.441 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 22.84% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.355 | 0.024 | 0.09% | 26.334..26.381 | stable | 26.362 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.695 | 0.000 | 0.01% | 3.695..3.696 | stable | 3.696 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.146 | 0.002 | 1.51% | 0.144..0.148 | stable | 0.144 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.483 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.443 | 0.005 | 1.23% | 0.437..0.448 | stable | 0.441 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 22.84% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.819 | 0.001 | 0.03% | stable | 4.522 | 0.297 |
| internal | 3 | 0.912 | 0.007 | 0.80% | stable | 0.504 | 0.409 |
| thread | 3 | 0.806 | 0.000 | 0.00% | stable | 0.801 | 0.005 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.520 | 0.037 | 0.21% | stable | 16.335 | 1.185 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.432 | 0.018 | 4.24% | stable | 0.064 | 0.368 |
| native_memory_tracking | 3 | 1.153 | 0.001 | 0.10% | stable | 0.941 | 0.212 |
| total | 3 | 565.974 | 0.014 | 0.00% | stable | 563.609 | 2.365 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 624.299 | 7.341 |
| counters | RssAnon | 3 | 598.332 | 6.549 |
| nmt | VmRSS | 3 | 621.423 | 0.663 |
| nmt | RssAnon | 3 | 595.757 | 0.477 |
| noprof | VmRSS | 1 | 591.523 | 0.000 |
| noprof | RssAnon | 1 | 570.348 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 19.56% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.002 | 0.001 | 33.26% | 0.001..0.002 | stable | 0.002 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.91% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.141 | 0.008 | 0.04% | 22.133..22.149 | stable | 22.144 |
| `native_mem_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.014 | 0.005 | 39.14% | 0.008..0.018 | stable | 0.014 |
| `native_mem_live_bytes.method_map` | 3 | 0.010 | 0.003 | 33.36% | 0.007..0.013 | stable | 0.011 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.14% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.203 | 0.040 | 0.17% | 23.168..23.246 | stable | 23.212 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.002 | 0.03% | 4.552..4.555 | stable | 4.555 |
| `native_mem_max_bytes.dictionary` | 3 | 4.599 | 0.030 | 0.66% | 4.573..4.632 | stable | 4.605 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.014 | 0.005 | 39.14% | 0.008..0.018 | stable | 0.014 |
| `native_mem_max_bytes.method_map` | 3 | 0.010 | 0.003 | 33.36% | 0.007..0.013 | stable | 0.011 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.13% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.141 | 0.008 | 0.04% | 22.133..22.149 | stable | 22.144 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.014 | 0.005 | 39.14% | 0.008..0.018 | stable | 0.014 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.010 | 0.003 | 33.36% | 0.007..0.013 | stable | 0.011 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.13% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.381 | 0.000 | 0.00% | stable | 0.270 | 0.111 |
| internal | 3 | 0.692 | 0.003 | 0.42% | stable | 0.527 | 0.165 |
| thread | 3 | 21.748 | 0.000 | 0.00% | stable | 21.743 | 0.005 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.438 | 0.001 | 0.01% | stable | 7.429 | 0.009 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.246 | 0.001 | 0.23% | stable | 0.198 | 0.048 |
| total | 3 | 559.465 | 0.065 | 0.01% | stable | 558.821 | 0.643 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 605.736 | 6.441 |
| counters | RssAnon | 3 | 580.102 | 5.616 |
| nmt | VmRSS | 3 | 602.307 | 0.167 |
| nmt | RssAnon | 3 | 577.160 | 0.022 |
| noprof | VmRSS | 1 | 576.523 | 0.000 |
| noprof | RssAnon | 1 | 556.566 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.058 | 0.001 | 1.02% | 0.057..0.058 | stable | 0.059 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.084 | 0.002 | 1.87% | 0.082..0.085 | stable | 0.086 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 3.94% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.367 | 0.015 | 0.06% | 23.357..23.384 | stable | 23.399 |
| `native_mem_live_bytes.calltrace` | 3 | 4.306 | 0.008 | 0.18% | 4.297..4.312 | stable | 4.313 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.565 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.166 | 0.001 | 0.68% | 0.165..0.167 | stable | 0.168 |
| `native_mem_live_bytes.method_map` | 3 | 0.503 | 0.009 | 1.87% | 0.494..0.512 | stable | 0.513 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.139 | 0.018 | 0.07% | 25.120..25.156 | stable | 25.166 |
| `native_mem_max_bytes.calltrace` | 3 | 5.517 | 0.011 | 0.19% | 5.505..5.525 | stable | 5.524 |
| `native_mem_max_bytes.dictionary` | 3 | 5.104 | 0.002 | 0.05% | 5.103..5.107 | stable | 5.112 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.166 | 0.001 | 0.68% | 0.165..0.167 | stable | 0.168 |
| `native_mem_max_bytes.method_map` | 3 | 0.503 | 0.009 | 1.87% | 0.494..0.512 | stable | 0.513 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.367 | 0.015 | 0.06% | 23.357..23.384 | stable | 23.399 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.628 | 0.001 | 0.02% | 3.627..3.629 | stable | 3.629 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.561 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.166 | 0.001 | 0.68% | 0.165..0.167 | stable | 0.168 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.503 | 0.009 | 1.87% | 0.494..0.512 | stable | 0.513 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.710 | 0.001 | 0.01% | stable | 8.251 | 0.459 |
| internal | 3 | 1.323 | 0.005 | 0.35% | stable | 0.700 | 0.623 |
| thread | 3 | 0.797 | 0.002 | 0.28% | stable | 0.801 | -0.004 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 26.041 | 4.389 | 16.85% | noisy | 21.651 | 4.389 |
| metaspace | 3 | 21.951 | 0.000 | 0.00% | stable | 21.753 | 0.198 |
| arena_chunk | 3 | 0.669 | 0.253 | 37.79% | noisy | 0.511 | 0.159 |
| native_memory_tracking | 3 | 2.008 | 0.046 | 2.27% | stable | 1.679 | 0.329 |
| total | 3 | 591.307 | 4.553 | 0.77% | stable | 585.146 | 6.161 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 644.607 | 2.666 |
| counters | RssAnon | 3 | 618.910 | 2.622 |
| nmt | VmRSS | 3 | 651.087 | 3.146 |
| nmt | RssAnon | 3 | 625.255 | 2.951 |
| noprof | VmRSS | 1 | 623.465 | 0.000 |
| noprof | RssAnon | 1 | 602.137 | 0.000 |
