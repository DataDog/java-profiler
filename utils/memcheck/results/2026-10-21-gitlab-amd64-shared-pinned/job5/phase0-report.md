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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 2.10% | 0.021..0.022 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.042 | 0.001 | 2.23% | 0.041..0.042 | stable | 0.041 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 15.10% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.682 | 0.009 | 0.04% | 24.675..24.693 | stable | 24.685 |
| `native_mem_live_bytes.calltrace` | 3 | 3.696 | 0.008 | 0.22% | 3.686..3.701 | stable | 3.699 |
| `native_mem_live_bytes.dictionary` | 3 | 6.799 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.098 | 0.004 | 4.10% | 0.094..0.102 | stable | 0.096 |
| `native_mem_live_bytes.method_map` | 3 | 0.250 | 0.006 | 2.23% | 0.243..0.253 | stable | 0.247 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 20.35% | 0.001..0.002 | stable | 0.001 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.866 | 0.018 | 0.07% | 25.846..25.878 | stable | 25.858 |
| `native_mem_max_bytes.calltrace` | 3 | 4.878 | 0.007 | 0.15% | 4.870..4.885 | stable | 4.872 |
| `native_mem_max_bytes.dictionary` | 3 | 6.799 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.098 | 0.004 | 4.10% | 0.094..0.102 | stable | 0.096 |
| `native_mem_max_bytes.method_map` | 3 | 0.250 | 0.006 | 2.23% | 0.243..0.253 | stable | 0.247 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 25.95% | 0.001..0.002 | stable | 0.001 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_max_observed_total_bytes` | 3 | 24.682 | 0.009 | 0.04% | 24.675..24.693 | stable | 24.685 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.000 | 0.01% | 3.566..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.045 | 0.007 | 0.11% | 6.041..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.098 | 0.004 | 4.10% | 0.094..0.102 | stable | 0.096 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.250 | 0.006 | 2.23% | 0.243..0.253 | stable | 0.247 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 25.95% | 0.001..0.002 | stable | 0.001 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.818 | 0.001 | 0.02% | stable | 4.521 | 0.297 |
| internal | 3 | 0.863 | 0.006 | 0.65% | stable | 0.504 | 0.359 |
| thread | 3 | 0.802 | 0.000 | 0.00% | stable | 0.801 | 0.001 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.484 | 0.157 | 0.90% | stable | 16.313 | 1.171 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.422 | 0.001 | 0.13% | stable | 0.390 | 0.032 |
| native_memory_tracking | 3 | 1.139 | 0.002 | 0.17% | stable | 0.936 | 0.203 |
| total | 3 | 565.879 | 0.128 | 0.02% | stable | 563.580 | 2.299 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 628.190 | 8.490 |
| counters | RssAnon | 3 | 601.997 | 7.655 |
| nmt | VmRSS | 3 | 619.621 | 0.321 |
| nmt | RssAnon | 3 | 594.160 | 0.231 |
| noprof | VmRSS | 1 | 591.668 | 0.000 |
| noprof | RssAnon | 1 | 570.543 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.127 | 0.007 | 5.68% | 0.120..0.134 | stable | 0.115 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.172 | 0.007 | 3.90% | 0.166..0.179 | stable | 0.161 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 11.55% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.533 | 0.070 | 0.26% | 26.484..26.613 | stable | 26.410 |
| `native_mem_live_bytes.calltrace` | 3 | 4.468 | 0.036 | 0.81% | 4.426..4.494 | stable | 4.441 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.392 | 0.021 | 5.25% | 0.372..0.413 | stable | 0.358 |
| `native_mem_live_bytes.method_map` | 3 | 1.031 | 0.040 | 3.89% | 0.994..1.074 | stable | 0.969 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 28.708 | 0.176 | 0.61% | 28.543..28.893 | stable | 28.388 |
| `native_mem_max_bytes.calltrace` | 3 | 6.634 | 0.115 | 1.73% | 6.525..6.754 | banded | 6.410 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.392 | 0.021 | 5.25% | 0.372..0.413 | stable | 0.358 |
| `native_mem_max_bytes.method_map` | 3 | 1.031 | 0.040 | 3.89% | 0.994..1.074 | stable | 0.969 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.533 | 0.070 | 0.26% | 26.484..26.613 | stable | 26.410 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.743 | 0.007 | 0.19% | 3.736..3.751 | stable | 3.732 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.392 | 0.021 | 5.25% | 0.372..0.413 | stable | 0.358 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 1.031 | 0.040 | 3.89% | 0.994..1.074 | stable | 0.969 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.461 | 2.938 |
| internal | 3 | 6.712 | 0.022 | 0.32% | stable | 3.476 | 3.237 |
| thread | 3 | 0.837 | 0.054 | 6.47% | stable | 0.805 | 0.032 |
| symbol | 3 | 5.878 | 0.000 | 0.00% | stable | 5.856 | 0.021 |
| code | 3 | 58.462 | 1.852 | 3.17% | banded | 55.806 | 2.656 |
| metaspace | 3 | 115.474 | 0.861 | 0.75% | stable | 116.433 | -0.959 |
| arena_chunk | 3 | 0.734 | 0.083 | 11.29% | noisy | 0.702 | 0.032 |
| native_memory_tracking | 3 | 11.521 | 0.420 | 3.65% | banded | 9.350 | 2.171 |
| total | 3 | 818.741 | 27.589 | 3.37% | banded | 793.066 | 25.675 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 865.130 | 12.058 |
| counters | RssAnon | 3 | 839.046 | 11.417 |
| nmt | VmRSS | 3 | 877.182 | 8.875 |
| nmt | RssAnon | 3 | 851.074 | 8.450 |
| noprof | VmRSS | 1 | 837.934 | 0.000 |
| noprof | RssAnon | 1 | 816.676 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.089 | 0.001 | 1.25% | 0.088..0.090 | stable | 0.090 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.074 | 0.000 | 0.62% | 0.073..0.074 | stable | 0.075 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 0.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.385 | 0.015 | 0.06% | 26.371..26.401 | stable | 26.335 |
| `native_mem_live_bytes.calltrace` | 3 | 4.666 | 0.019 | 0.41% | 4.645..4.682 | stable | 4.607 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.32% | 0.148..0.155 | stable | 0.146 |
| `native_mem_live_bytes.liveness` | 3 | 0.483 | 0.000 | 0.00% | 0.483..0.483 | stable | 0.489 |
| `native_mem_live_bytes.method_map` | 3 | 0.442 | 0.003 | 0.62% | 0.439..0.444 | stable | 0.449 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.82% | 0.053..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.711 | 0.025 | 0.09% | 27.683..27.733 | stable | 27.722 |
| `native_mem_max_bytes.calltrace` | 3 | 5.983 | 0.019 | 0.32% | 5.962..5.998 | stable | 5.985 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.32% | 0.148..0.155 | stable | 0.146 |
| `native_mem_max_bytes.liveness` | 3 | 0.483 | 0.000 | 0.00% | 0.483..0.483 | stable | 0.489 |
| `native_mem_max_bytes.method_map` | 3 | 0.442 | 0.003 | 0.62% | 0.439..0.444 | stable | 0.449 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.385 | 0.015 | 0.06% | 26.371..26.401 | stable | 26.335 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.695 | 0.001 | 0.03% | 3.694..3.696 | stable | 3.696 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.32% | 0.148..0.155 | stable | 0.146 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.483 | 0.000 | 0.00% | 0.483..0.483 | stable | 0.489 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.442 | 0.003 | 0.62% | 0.439..0.444 | stable | 0.449 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.820 | 0.002 | 0.04% | stable | 4.522 | 0.298 |
| internal | 3 | 0.945 | 0.046 | 4.90% | stable | 0.503 | 0.442 |
| thread | 3 | 0.841 | 0.061 | 7.24% | stable | 0.801 | 0.040 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.587 | 0.053 | 0.30% | stable | 16.281 | 1.306 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.442 | 0.036 | 8.10% | stable | 0.390 | 0.052 |
| native_memory_tracking | 3 | 1.231 | 0.138 | 11.22% | noisy | 0.941 | 0.290 |
| total | 3 | 581.711 | 27.187 | 4.67% | banded | 563.552 | 18.159 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 620.062 | 0.131 |
| counters | RssAnon | 3 | 594.417 | 0.219 |
| nmt | VmRSS | 3 | 631.555 | 14.878 |
| nmt | RssAnon | 3 | 605.530 | 14.177 |
| noprof | VmRSS | 1 | 591.754 | 0.000 |
| noprof | RssAnon | 1 | 570.773 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 15.05% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.002 | 0.000 | 29.91% | 0.001..0.002 | stable | 0.002 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.64% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.139 | 0.007 | 0.03% | 22.131..22.145 | stable | 22.144 |
| `native_mem_live_bytes.calltrace` | 3 | 3.547 | 0.000 | 0.01% | 3.546..3.547 | stable | 3.547 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.012 | 0.005 | 43.12% | 0.006..0.017 | stable | 0.014 |
| `native_mem_live_bytes.method_map` | 3 | 0.009 | 0.003 | 29.89% | 0.006..0.011 | stable | 0.010 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.99% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.21% | 0.205..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.197 | 0.027 | 0.12% | 23.165..23.216 | stable | 23.202 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.02% | 4.553..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.594 | 0.019 | 0.41% | 4.573..4.607 | stable | 4.596 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.012 | 0.005 | 43.12% | 0.006..0.017 | stable | 0.014 |
| `native_mem_max_bytes.method_map` | 3 | 0.009 | 0.003 | 29.89% | 0.006..0.011 | stable | 0.010 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.85% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.21% | 0.206..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.139 | 0.007 | 0.03% | 22.131..22.145 | stable | 22.144 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.012 | 0.005 | 43.12% | 0.006..0.017 | stable | 0.014 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.009 | 0.003 | 29.89% | 0.006..0.011 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.85% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.21% | 0.206..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.382 | 0.001 | 0.30% | stable | 0.270 | 0.112 |
| internal | 3 | 0.704 | 0.014 | 2.01% | stable | 0.527 | 0.177 |
| thread | 3 | 21.771 | 0.040 | 0.18% | stable | 21.743 | 0.028 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.02% | stable | 7.428 | 0.011 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.325 | 0.250 |
| arena_chunk | 3 | 0.049 | 0.073 | 148.96% | noisy | 0.007 | 0.042 |
| native_memory_tracking | 3 | 0.272 | 0.045 | 16.70% | stable | 0.199 | 0.073 |
| total | 3 | 574.903 | 26.728 | 4.65% | banded | 558.866 | 16.037 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 606.159 | 6.784 |
| counters | RssAnon | 3 | 580.599 | 6.085 |
| nmt | VmRSS | 3 | 606.392 | 6.949 |
| nmt | RssAnon | 3 | 580.845 | 6.123 |
| noprof | VmRSS | 1 | 576.719 | 0.000 |
| noprof | RssAnon | 1 | 556.570 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.059 | 0.001 | 2.47% | 0.057..0.060 | stable | 0.060 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.083 | 0.002 | 2.40% | 0.082..0.086 | stable | 0.085 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 9.96% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.363 | 0.047 | 0.20% | 23.310..23.398 | stable | 23.379 |
| `native_mem_live_bytes.calltrace` | 3 | 4.285 | 0.033 | 0.77% | 4.247..4.308 | stable | 4.289 |
| `native_mem_live_bytes.dictionary` | 3 | 4.570 | 0.000 | 0.00% | 4.570..4.570 | stable | 4.576 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.168 | 0.007 | 4.00% | 0.162..0.175 | stable | 0.165 |
| `native_mem_live_bytes.method_map` | 3 | 0.501 | 0.012 | 2.40% | 0.490..0.514 | stable | 0.508 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.148 | 0.065 | 0.26% | 25.087..25.217 | stable | 25.171 |
| `native_mem_max_bytes.calltrace` | 3 | 5.515 | 0.044 | 0.79% | 5.474..5.561 | stable | 5.529 |
| `native_mem_max_bytes.dictionary` | 3 | 5.117 | 0.004 | 0.08% | 5.112..5.119 | stable | 5.120 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.168 | 0.007 | 4.00% | 0.162..0.175 | stable | 0.165 |
| `native_mem_max_bytes.method_map` | 3 | 0.501 | 0.012 | 2.40% | 0.490..0.514 | stable | 0.508 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.363 | 0.047 | 0.20% | 23.310..23.398 | stable | 23.379 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.629 | 0.001 | 0.04% | 3.628..3.630 | stable | 3.630 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.565 | 0.000 | 0.00% | 4.565..4.565 | stable | 4.568 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.168 | 0.007 | 4.00% | 0.162..0.175 | stable | 0.165 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.501 | 0.012 | 2.40% | 0.490..0.514 | stable | 0.508 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.711 | 0.002 | 0.02% | stable | 8.251 | 0.460 |
| internal | 3 | 1.348 | 0.036 | 2.70% | stable | 0.698 | 0.650 |
| thread | 3 | 0.828 | 0.055 | 6.68% | stable | 0.797 | 0.031 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 24.824 | 1.357 | 5.47% | noisy | 22.324 | 2.499 |
| metaspace | 3 | 21.961 | 0.017 | 0.08% | stable | 21.753 | 0.208 |
| arena_chunk | 3 | 0.521 | 0.079 | 15.18% | noisy | 0.379 | 0.143 |
| native_memory_tracking | 3 | 2.112 | 0.203 | 9.60% | noisy | 1.689 | 0.423 |
| total | 3 | 605.705 | 28.070 | 4.63% | banded | 585.898 | 19.807 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 649.501 | 10.027 |
| counters | RssAnon | 3 | 623.254 | 9.496 |
| nmt | VmRSS | 3 | 653.294 | 9.435 |
| nmt | RssAnon | 3 | 627.188 | 8.951 |
| noprof | VmRSS | 1 | 617.559 | 0.000 |
| noprof | RssAnon | 1 | 596.250 | 0.000 |
