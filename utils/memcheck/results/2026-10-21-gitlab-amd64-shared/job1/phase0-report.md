# Phase 0: memcheck noise

- profiler-commit: `7cd55c5ec9ca24e5e6eb59cd76b052a94f6e5138`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS` (jdk.txt captured the JAVA_TOOL_OPTIONS line; version from runner.txt)
- cpus: `66`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.024 | 0.001 | 3.87% | 0.023..0.025 | stable | 0.023 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.047 | 0.001 | 2.82% | 0.046..0.048 | stable | 0.045 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 10.69% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 24.724 | 0.011 | 0.04% | 24.716..24.736 | stable | 24.728 |
| `native_mem_live_bytes.calltrace` | 3 | 3.693 | 0.001 | 0.02% | 3.692..3.694 | stable | 3.705 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.106 | 0.003 | 2.72% | 0.104..0.109 | stable | 0.105 |
| `native_mem_live_bytes.method_map` | 3 | 0.279 | 0.008 | 2.82% | 0.275..0.288 | stable | 0.270 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.005 | 0.001 | 11.96% | 0.005..0.006 | stable | 0.005 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 25.957 | 0.024 | 0.09% | 25.941..25.984 | stable | 25.938 |
| `native_mem_max_bytes.calltrace` | 3 | 4.916 | 0.014 | 0.29% | 4.904..4.932 | stable | 4.906 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.106 | 0.003 | 2.72% | 0.104..0.109 | stable | 0.105 |
| `native_mem_max_bytes.method_map` | 3 | 0.279 | 0.008 | 2.82% | 0.275..0.288 | stable | 0.270 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.007 | 0.001 | 10.72% | 0.007..0.008 | stable | 0.007 |
| `native_mem_max_bytes.thread_local` | 3 | 0.062 | 0.001 | 1.43% | 0.061..0.063 | stable | 0.062 |
| `native_mem_max_observed_total_bytes` | 3 | 24.724 | 0.011 | 0.04% | 24.716..24.736 | stable | 24.728 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.569 | 0.001 | 0.03% | 3.569..3.570 | stable | 3.569 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.106 | 0.003 | 2.72% | 0.104..0.109 | stable | 0.105 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.279 | 0.008 | 2.82% | 0.275..0.288 | stable | 0.270 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 10.72% | 0.007..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.058 | 0.001 | 1.53% | 0.057..0.059 | stable | 0.057 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.843 | 0.002 | 0.05% | stable | 4.586 | 0.257 |
| internal | 3 | 1.002 | 0.004 | 0.41% | stable | 0.640 | 0.362 |
| thread | 3 | 1.560 | 0.157 | 10.04% | noisy | 1.761 | -0.201 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 20.915 | 0.384 | 1.84% | banded | 22.255 | -1.340 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.096 | 0.000 | 0.00% | stable | 0.002 | 0.094 |
| native_memory_tracking | 3 | 1.482 | 0.007 | 0.46% | stable | 1.369 | 0.113 |
| total | 3 | 698.791 | 8.786 | 1.26% | banded | 708.836 | -10.045 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 659.258 | 9.763 |
| counters | RssAnon | 3 | 632.661 | 9.753 |
| nmt | VmRSS | 3 | 651.319 | 1.333 |
| nmt | RssAnon | 3 | 624.826 | 1.203 |
| noprof | VmRSS | 1 | 642.320 | 0.000 |
| noprof | RssAnon | 1 | 619.926 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.108 | 0.001 | 0.81% | 0.107..0.109 | stable | 0.112 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.154 | 0.001 | 0.41% | 0.154..0.155 | stable | 0.157 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 5.55% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.380 | 0.003 | 0.01% | 26.377..26.383 | stable | 26.388 |
| `native_mem_live_bytes.calltrace` | 3 | 4.455 | 0.007 | 0.15% | 4.447..4.461 | stable | 4.438 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.334 | 0.003 | 0.86% | 0.331..0.337 | stable | 0.342 |
| `native_mem_live_bytes.method_map` | 3 | 0.926 | 0.004 | 0.42% | 0.922..0.929 | stable | 0.945 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.009 | 0.001 | 6.76% | 0.008..0.009 | stable | 0.008 |
| `native_mem_live_bytes.thread_local` | 3 | 0.068 | 0.002 | 3.22% | 0.067..0.071 | stable | 0.068 |
| `native_mem_max_bytes` | 3 | 28.219 | 0.020 | 0.07% | 28.196..28.231 | stable | 28.305 |
| `native_mem_max_bytes.calltrace` | 3 | 6.284 | 0.023 | 0.36% | 6.259..6.302 | stable | 6.344 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.334 | 0.003 | 0.86% | 0.331..0.337 | stable | 0.342 |
| `native_mem_max_bytes.method_map` | 3 | 0.926 | 0.004 | 0.42% | 0.922..0.929 | stable | 0.945 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.001 | 6.76% | 0.008..0.009 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.070 | 0.000 | 0.63% | 0.070..0.071 | stable | 0.071 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.380 | 0.003 | 0.01% | 26.377..26.383 | stable | 26.388 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.724 | 0.001 | 0.02% | 3.723..3.725 | stable | 3.728 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.334 | 0.003 | 0.86% | 0.331..0.337 | stable | 0.342 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.926 | 0.004 | 0.42% | 0.922..0.929 | stable | 0.945 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 10.43% | 0.006..0.007 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.062 | 0.001 | 1.87% | 0.061..0.063 | stable | 0.063 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.416 | 0.001 | 0.00% | stable | 65.480 | 2.936 |
| internal | 3 | 6.798 | 0.019 | 0.27% | stable | 3.596 | 3.202 |
| thread | 3 | 2.014 | 0.042 | 2.10% | stable | 2.299 | -0.285 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 64.821 | 0.942 | 1.45% | banded | 57.551 | 7.271 |
| metaspace | 3 | 115.743 | 0.247 | 0.21% | stable | 117.188 | -1.445 |
| arena_chunk | 3 | 3.122 | 0.812 | 26.02% | noisy | 3.931 | -0.809 |
| native_memory_tracking | 3 | 12.128 | 0.036 | 0.30% | stable | 10.129 | 1.999 |
| total | 3 | 947.648 | 13.518 | 1.43% | banded | 952.438 | -4.789 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 922.611 | 5.550 |
| counters | RssAnon | 3 | 895.780 | 5.649 |
| nmt | VmRSS | 3 | 933.811 | 11.912 |
| nmt | RssAnon | 3 | 906.978 | 11.796 |
| noprof | VmRSS | 1 | 894.762 | 0.000 |
| noprof | RssAnon | 1 | 872.324 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.087 | 0.001 | 1.14% | 0.086..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.002 | 2.88% | 0.071..0.076 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 10.49% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.056 | 0.030 | 0.12% | 26.037..26.091 | stable | 26.052 |
| `native_mem_live_bytes.calltrace` | 3 | 4.335 | 0.017 | 0.39% | 4.317..4.350 | stable | 4.333 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.134 | 0.007 | 5.59% | 0.127..0.141 | stable | 0.131 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.440 | 0.013 | 2.88% | 0.428..0.453 | stable | 0.441 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.005 | 0.001 | 11.79% | 0.004..0.005 | stable | 0.005 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.652 | 0.032 | 0.11% | 27.616..27.676 | stable | 27.662 |
| `native_mem_max_bytes.calltrace` | 3 | 5.910 | 0.014 | 0.23% | 5.895..5.921 | stable | 5.923 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.01% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.134 | 0.007 | 5.59% | 0.127..0.141 | stable | 0.131 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.440 | 0.013 | 2.88% | 0.428..0.453 | stable | 0.441 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.010 | 0.001 | 6.87% | 0.009..0.010 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.062 | 0.001 | 1.41% | 0.062..0.063 | stable | 0.062 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.056 | 0.030 | 0.12% | 26.037..26.091 | stable | 26.052 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.02% | 3.693..3.695 | stable | 3.695 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.134 | 0.007 | 5.59% | 0.127..0.141 | stable | 0.131 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.440 | 0.013 | 2.88% | 0.428..0.453 | stable | 0.441 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.010 | 0.001 | 6.87% | 0.009..0.010 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.057 | 0.001 | 2.05% | 0.056..0.058 | stable | 0.057 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.840 | 0.005 | 0.10% | stable | 4.581 | 0.259 |
| internal | 3 | 1.031 | 0.011 | 1.10% | stable | 0.646 | 0.384 |
| thread | 3 | 1.551 | 0.124 | 8.00% | noisy | 1.785 | -0.234 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 20.562 | 0.546 | 2.65% | banded | 21.592 | -1.029 |
| metaspace | 3 | 11.495 | 0.036 | 0.31% | stable | 11.266 | 0.229 |
| arena_chunk | 3 | 0.695 | 1.037 | 149.23% | noisy | 0.034 | 0.661 |
| native_memory_tracking | 3 | 1.482 | 0.013 | 0.87% | stable | 1.355 | 0.127 |
| total | 3 | 705.175 | 20.669 | 2.93% | banded | 728.513 | -23.338 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 661.202 | 17.897 |
| counters | RssAnon | 3 | 634.408 | 17.958 |
| nmt | VmRSS | 3 | 652.633 | 2.845 |
| nmt | RssAnon | 3 | 625.663 | 2.861 |
| noprof | VmRSS | 1 | 625.578 | 0.000 |
| noprof | RssAnon | 1 | 603.145 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 12.76% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 16.84% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 1.26% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.132 | 0.001 | 0.00% | 22.132..22.134 | stable | 22.139 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.004 | 0.001 | 20.11% | 0.003..0.005 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.001 | 17.49% | 0.005..0.007 | stable | 0.007 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.031 | 0.001 | 1.92% | 0.031..0.032 | stable | 0.031 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.161 | 0.003 | 0.01% | 23.157..23.164 | stable | 23.175 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.01% | 4.553..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.566 | 0.002 | 0.05% | 4.564..4.568 | stable | 4.574 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.004 | 0.001 | 20.11% | 0.003..0.005 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.001 | 17.49% | 0.005..0.007 | stable | 0.007 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.031 | 0.001 | 1.91% | 0.031..0.032 | stable | 0.031 |
| `native_mem_max_bytes.thread_local` | 3 | 0.208 | 0.000 | 0.00% | 0.208..0.208 | stable | 0.208 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.134 | 0.000 | 0.00% | 22.133..22.134 | stable | 22.139 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.004 | 0.001 | 20.11% | 0.003..0.005 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.001 | 17.49% | 0.005..0.007 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.031 | 0.001 | 1.91% | 0.031..0.032 | stable | 0.031 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.394 | 0.002 | 0.52% | stable | 0.281 | 0.113 |
| internal | 3 | 0.764 | 0.005 | 0.68% | stable | 0.603 | 0.161 |
| thread | 3 | 22.285 | 0.089 | 0.40% | stable | 22.257 | 0.028 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.444 | 0.000 | 0.00% | stable | 7.437 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.008 | 0.001 | 6.93% | stable | 0.008 | 0.000 |
| native_memory_tracking | 3 | 0.348 | 0.005 | 1.32% | stable | 0.296 | 0.052 |
| total | 3 | 699.003 | 17.975 | 2.57% | banded | 692.732 | 6.271 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 615.820 | 0.599 |
| counters | RssAnon | 3 | 589.284 | 0.693 |
| nmt | VmRSS | 3 | 616.111 | 0.733 |
| nmt | RssAnon | 3 | 589.674 | 0.519 |
| noprof | VmRSS | 1 | 591.754 | 0.000 |
| noprof | RssAnon | 1 | 570.246 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.001 | 1.78% | 0.055..0.057 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.001 | 0.75% | 0.075..0.076 | stable | 0.075 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 10.31% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 23.313 | 0.018 | 0.08% | 23.293..23.325 | stable | 23.302 |
| `native_mem_live_bytes.calltrace` | 3 | 4.320 | 0.012 | 0.27% | 4.307..4.330 | stable | 4.316 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.13% | 0.131..0.139 | stable | 0.132 |
| `native_mem_live_bytes.method_map` | 3 | 0.452 | 0.003 | 0.75% | 0.449..0.455 | stable | 0.448 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.001 | 12.60% | 0.005..0.007 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.062 | 0.002 | 2.56% | 0.060..0.063 | stable | 0.062 |
| `native_mem_max_bytes` | 3 | 24.991 | 0.014 | 0.05% | 24.976..25.004 | stable | 24.974 |
| `native_mem_max_bytes.calltrace` | 3 | 5.431 | 0.014 | 0.25% | 5.420..5.446 | stable | 5.425 |
| `native_mem_max_bytes.dictionary` | 3 | 5.096 | 0.004 | 0.09% | 5.092..5.100 | stable | 5.094 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.13% | 0.131..0.139 | stable | 0.132 |
| `native_mem_max_bytes.method_map` | 3 | 0.452 | 0.003 | 0.75% | 0.449..0.455 | stable | 0.448 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.001 | 13.94% | 0.008..0.010 | stable | 0.009 |
| `native_mem_max_bytes.thread_local` | 3 | 0.074 | 0.003 | 3.89% | 0.071..0.076 | stable | 0.073 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.313 | 0.018 | 0.08% | 23.293..23.325 | stable | 23.302 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.626 | 0.001 | 0.03% | 3.625..3.627 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.135 | 0.004 | 3.13% | 0.131..0.139 | stable | 0.132 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.452 | 0.003 | 0.75% | 0.449..0.455 | stable | 0.448 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.009 | 0.001 | 13.94% | 0.008..0.010 | stable | 0.009 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.066 | 0.002 | 3.04% | 0.064..0.068 | stable | 0.066 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.729 | 0.002 | 0.03% | stable | 8.269 | 0.460 |
| internal | 3 | 1.431 | 0.011 | 0.78% | stable | 0.836 | 0.595 |
| thread | 3 | 1.946 | 0.185 | 9.52% | noisy | 1.873 | 0.073 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 53.384 | 0.310 | 0.58% | stable | 47.044 | 6.340 |
| metaspace | 3 | 21.998 | 0.082 | 0.37% | stable | 21.753 | 0.245 |
| arena_chunk | 3 | 0.506 | 0.871 | 172.37% | noisy | 0.003 | 0.503 |
| native_memory_tracking | 3 | 2.645 | 0.004 | 0.15% | stable | 2.325 | 0.320 |
| total | 3 | 759.460 | 18.079 | 2.38% | banded | 746.125 | 13.335 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 717.540 | 1.372 |
| counters | RssAnon | 3 | 690.615 | 1.575 |
| nmt | VmRSS | 3 | 720.788 | 4.366 |
| nmt | RssAnon | 3 | 693.980 | 4.176 |
| noprof | VmRSS | 1 | 691.418 | 0.000 |
| noprof | RssAnon | 1 | 668.945 | 0.000 |
