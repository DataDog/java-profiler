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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.022 | 0.000 | 2.08% | 0.022..0.023 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.044 | 0.001 | 1.28% | 0.043..0.044 | stable | 0.041 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 14.18% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.723 | 0.004 | 0.02% | 24.720..24.728 | stable | 24.703 |
| `native_mem_live_bytes.calltrace` | 3 | 3.716 | 0.005 | 0.14% | 3.711..3.722 | stable | 3.719 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.801 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.102 | 0.002 | 2.41% | 0.100..0.104 | stable | 0.095 |
| `native_mem_live_bytes.method_map` | 3 | 0.262 | 0.003 | 1.28% | 0.258..0.265 | stable | 0.247 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 19.10% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.904 | 0.013 | 0.05% | 25.889..25.913 | stable | 25.860 |
| `native_mem_max_bytes.calltrace` | 3 | 4.896 | 0.008 | 0.16% | 4.888..4.903 | stable | 4.875 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.801 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.102 | 0.002 | 2.41% | 0.100..0.104 | stable | 0.095 |
| `native_mem_max_bytes.method_map` | 3 | 0.262 | 0.003 | 1.28% | 0.258..0.265 | stable | 0.247 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.001 | 28.57% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.723 | 0.004 | 0.02% | 24.720..24.728 | stable | 24.703 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.568 | 0.000 | 0.01% | 3.567..3.568 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.049 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.102 | 0.002 | 2.41% | 0.100..0.104 | stable | 0.095 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.262 | 0.003 | 1.28% | 0.258..0.265 | stable | 0.247 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.001 | 28.57% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.821 | 0.002 | 0.05% | stable | 4.528 | 0.293 |
| internal | 3 | 0.917 | 0.051 | 5.56% | stable | 0.589 | 0.328 |
| thread | 3 | 0.896 | 0.084 | 9.41% | noisy | 0.960 | -0.064 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.087 | 0.575 | 3.18% | banded | 16.849 | 1.238 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.453 | 0.375 | 82.76% | noisy | 0.780 | -0.327 |
| native_memory_tracking | 3 | 1.326 | 0.160 | 12.07% | noisy | 1.220 | 0.106 |
| total | 3 | 600.528 | 30.031 | 5.00% | noisy | 615.602 | -15.073 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 628.102 | 8.699 |
| counters | RssAnon | 3 | 601.900 | 7.885 |
| nmt | VmRSS | 3 | 630.548 | 9.583 |
| nmt | RssAnon | 3 | 604.529 | 8.821 |
| noprof | VmRSS | 1 | 605.129 | 0.000 |
| noprof | RssAnon | 1 | 582.945 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.121 | 0.010 | 8.34% | 0.112..0.132 | stable | 0.112 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.167 | 0.010 | 5.93% | 0.158..0.178 | stable | 0.159 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 27.71% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.484 | 0.138 | 0.52% | 26.339..26.614 | stable | 26.394 |
| `native_mem_live_bytes.calltrace` | 3 | 4.464 | 0.055 | 1.22% | 4.401..4.498 | stable | 4.446 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.374 | 0.031 | 8.35% | 0.344..0.407 | stable | 0.349 |
| `native_mem_live_bytes.method_map` | 3 | 1.003 | 0.060 | 5.96% | 0.949..1.067 | stable | 0.954 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.001 | 33.58% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.82% | 0.053..0.054 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 28.534 | 0.280 | 0.98% | 28.269..28.826 | stable | 28.314 |
| `native_mem_max_bytes.calltrace` | 3 | 6.506 | 0.189 | 2.91% | 6.323..6.701 | banded | 6.359 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.374 | 0.031 | 8.35% | 0.344..0.407 | stable | 0.349 |
| `native_mem_max_bytes.method_map` | 3 | 1.003 | 0.060 | 5.96% | 0.949..1.067 | stable | 0.954 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 27.27% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.484 | 0.138 | 0.52% | 26.339..26.614 | stable | 26.394 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.737 | 0.010 | 0.27% | 3.729..3.748 | stable | 3.729 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.374 | 0.031 | 8.35% | 0.344..0.407 | stable | 0.349 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 1.003 | 0.060 | 5.96% | 0.949..1.067 | stable | 0.954 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 21.29% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.400 | 0.001 | 0.00% | stable | 65.460 | 2.940 |
| internal | 3 | 6.701 | 0.032 | 0.48% | stable | 3.530 | 3.171 |
| thread | 3 | 0.850 | 0.074 | 8.69% | noisy | 0.924 | -0.074 |
| symbol | 3 | 5.877 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 58.946 | 0.965 | 1.64% | banded | 53.156 | 5.790 |
| metaspace | 3 | 115.582 | 0.996 | 0.86% | stable | 117.100 | -1.518 |
| arena_chunk | 3 | 0.692 | 0.018 | 2.57% | stable | 0.576 | 0.116 |
| native_memory_tracking | 3 | 11.532 | 0.453 | 3.92% | banded | 10.020 | 1.512 |
| total | 3 | 820.673 | 31.603 | 3.85% | banded | 841.488 | -20.815 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 860.236 | 10.003 |
| counters | RssAnon | 3 | 834.267 | 9.447 |
| nmt | VmRSS | 3 | 875.246 | 10.422 |
| nmt | RssAnon | 3 | 849.247 | 9.732 |
| noprof | VmRSS | 1 | 849.027 | 0.000 |
| noprof | RssAnon | 1 | 826.766 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.087 | 0.002 | 2.85% | 0.084..0.089 | stable | 0.087 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.001 | 1.31% | 0.072..0.074 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 16.04% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.208 | 0.075 | 0.29% | 26.148..26.292 | stable | 26.250 |
| `native_mem_live_bytes.calltrace` | 3 | 4.499 | 0.084 | 1.88% | 4.429..4.592 | banded | 4.536 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.30% | 0.132..0.140 | stable | 0.138 |
| `native_mem_live_bytes.liveness` | 3 | 0.494 | 0.010 | 1.97% | 0.483..0.500 | stable | 0.494 |
| `native_mem_live_bytes.method_map` | 3 | 0.436 | 0.006 | 1.32% | 0.432..0.443 | stable | 0.438 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 21.40% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.656 | 0.042 | 0.15% | 27.610..27.690 | stable | 27.669 |
| `native_mem_max_bytes.calltrace` | 3 | 5.937 | 0.040 | 0.68% | 5.891..5.961 | stable | 5.946 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.30% | 0.132..0.140 | stable | 0.138 |
| `native_mem_max_bytes.liveness` | 3 | 0.494 | 0.010 | 1.97% | 0.483..0.500 | stable | 0.494 |
| `native_mem_max_bytes.method_map` | 3 | 0.436 | 0.006 | 1.32% | 0.432..0.443 | stable | 0.438 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.001 | 34.86% | 0.002..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.208 | 0.075 | 0.29% | 26.148..26.292 | stable | 26.250 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.693 | 0.003 | 0.07% | 3.691..3.696 | stable | 3.693 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.30% | 0.132..0.140 | stable | 0.138 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.494 | 0.010 | 1.97% | 0.483..0.500 | stable | 0.494 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.436 | 0.006 | 1.32% | 0.432..0.443 | stable | 0.438 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.001 | 34.86% | 0.002..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.821 | 0.001 | 0.02% | stable | 4.527 | 0.294 |
| internal | 3 | 0.963 | 0.040 | 4.19% | stable | 0.588 | 0.375 |
| thread | 3 | 0.902 | 0.086 | 9.58% | noisy | 0.964 | -0.062 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.215 | 0.426 | 2.34% | banded | 16.913 | 1.301 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.464 | 0.374 | 80.71% | noisy | 0.748 | -0.285 |
| native_memory_tracking | 3 | 1.339 | 0.160 | 11.98% | noisy | 1.222 | 0.117 |
| total | 3 | 600.740 | 29.910 | 4.98% | banded | 615.633 | -14.893 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 630.932 | 8.700 |
| counters | RssAnon | 3 | 604.642 | 7.907 |
| nmt | VmRSS | 3 | 631.439 | 8.938 |
| nmt | RssAnon | 3 | 605.034 | 8.309 |
| noprof | VmRSS | 1 | 605.621 | 0.000 |
| noprof | RssAnon | 1 | 583.359 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 5.41% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.001 | 61.62% | 0.001..0.002 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.96% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.135 | 0.007 | 0.03% | 22.130..22.143 | stable | 22.141 |
| `native_mem_live_bytes.calltrace` | 3 | 3.547 | 0.001 | 0.02% | 3.547..3.548 | stable | 3.547 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.009 | 0.004 | 41.04% | 0.006..0.013 | stable | 0.013 |
| `native_mem_live_bytes.method_map` | 3 | 0.007 | 0.004 | 62.26% | 0.004..0.012 | stable | 0.008 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.13% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.182 | 0.039 | 0.17% | 23.158..23.227 | stable | 23.196 |
| `native_mem_max_bytes.calltrace` | 3 | 4.553 | 0.001 | 0.03% | 4.552..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.585 | 0.030 | 0.66% | 4.567..4.620 | stable | 4.593 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.009 | 0.004 | 41.04% | 0.006..0.013 | stable | 0.013 |
| `native_mem_max_bytes.method_map` | 3 | 0.007 | 0.004 | 62.26% | 0.004..0.012 | stable | 0.008 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.12% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.135 | 0.007 | 0.03% | 22.130..22.143 | stable | 22.141 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.009 | 0.004 | 41.04% | 0.006..0.013 | stable | 0.013 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.007 | 0.004 | 62.26% | 0.004..0.012 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.12% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.382 | 0.001 | 0.30% | stable | 0.271 | 0.112 |
| internal | 3 | 0.715 | 0.014 | 1.99% | stable | 0.563 | 0.152 |
| thread | 3 | 21.802 | 0.048 | 0.22% | stable | 21.812 | -0.010 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.000 | 0.00% | stable | 7.432 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.049 | 0.072 | 148.79% | noisy | 0.133 | -0.084 |
| native_memory_tracking | 3 | 0.298 | 0.046 | 15.41% | stable | 0.277 | 0.021 |
| total | 3 | 591.642 | 28.095 | 4.75% | banded | 605.149 | -13.507 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 609.230 | 6.422 |
| counters | RssAnon | 3 | 583.240 | 5.610 |
| nmt | VmRSS | 3 | 609.440 | 6.416 |
| nmt | RssAnon | 3 | 583.579 | 5.769 |
| noprof | VmRSS | 1 | 588.656 | 0.000 |
| noprof | RssAnon | 1 | 567.238 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.003 | 5.97% | 0.054..0.060 | stable | 0.056 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.081 | 0.005 | 6.04% | 0.078..0.087 | stable | 0.082 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 21.02% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.314 | 0.078 | 0.34% | 23.254..23.402 | stable | 23.337 |
| `native_mem_live_bytes.calltrace` | 3 | 4.277 | 0.039 | 0.91% | 4.240..4.317 | stable | 4.286 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.157 | 0.012 | 7.80% | 0.149..0.172 | stable | 0.159 |
| `native_mem_live_bytes.method_map` | 3 | 0.487 | 0.029 | 6.04% | 0.469..0.520 | stable | 0.493 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 25.28% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.035 | 0.130 | 0.52% | 24.952..25.185 | stable | 25.075 |
| `native_mem_max_bytes.calltrace` | 3 | 5.444 | 0.085 | 1.56% | 5.385..5.541 | banded | 5.468 |
| `native_mem_max_bytes.dictionary` | 3 | 5.098 | 0.005 | 0.09% | 5.094..5.103 | stable | 5.105 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.157 | 0.012 | 7.80% | 0.149..0.172 | stable | 0.159 |
| `native_mem_max_bytes.method_map` | 3 | 0.487 | 0.029 | 6.04% | 0.469..0.520 | stable | 0.493 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 25.02% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.314 | 0.078 | 0.34% | 23.254..23.402 | stable | 23.337 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.626 | 0.003 | 0.09% | 3.624..3.630 | stable | 3.626 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.157 | 0.012 | 7.80% | 0.149..0.172 | stable | 0.159 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.487 | 0.029 | 6.04% | 0.469..0.520 | stable | 0.493 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 25.02% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.711 | 0.002 | 0.02% | stable | 8.251 | 0.460 |
| internal | 3 | 1.340 | 0.036 | 2.70% | stable | 0.698 | 0.642 |
| thread | 3 | 0.855 | 0.099 | 11.54% | noisy | 0.797 | 0.058 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 26.054 | 2.249 | 8.63% | noisy | 22.442 | 3.612 |
| metaspace | 3 | 21.951 | 0.000 | 0.00% | stable | 21.753 | 0.198 |
| arena_chunk | 3 | 0.679 | 0.770 | 113.38% | noisy | 0.922 | -0.243 |
| native_memory_tracking | 3 | 2.116 | 0.207 | 9.77% | noisy | 1.690 | 0.425 |
| total | 3 | 608.446 | 32.473 | 5.34% | noisy | 586.174 | 22.272 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 663.243 | 14.494 |
| counters | RssAnon | 3 | 636.863 | 14.080 |
| nmt | VmRSS | 3 | 656.367 | 18.027 |
| nmt | RssAnon | 3 | 630.267 | 17.249 |
| noprof | VmRSS | 1 | 614.305 | 0.000 |
| noprof | RssAnon | 1 | 593.266 | 0.000 |
