# Phase 0: memcheck noise

- profiler-commit: `7cd55c5ec9ca24e5e6eb59cd76b052a94f6e5138`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS` (jdk.txt captured the JAVA_TOOL_OPTIONS line; version from runner.txt)
- cpus: `52`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.024 | 0.000 | 1.01% | 0.023..0.024 | stable | 0.023 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.047 | 0.001 | 1.42% | 0.046..0.047 | stable | 0.045 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 7.62% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 24.731 | 0.011 | 0.05% | 24.720..24.742 | stable | 24.722 |
| `native_mem_live_bytes.calltrace` | 3 | 3.695 | 0.002 | 0.06% | 3.692..3.696 | stable | 3.697 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.111 | 0.007 | 5.87% | 0.106..0.118 | stable | 0.104 |
| `native_mem_live_bytes.method_map` | 3 | 0.279 | 0.004 | 1.42% | 0.275..0.282 | stable | 0.272 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.005 | 0.000 | 8.46% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 25.962 | 0.013 | 0.05% | 25.949..25.974 | stable | 25.944 |
| `native_mem_max_bytes.calltrace` | 3 | 4.914 | 0.003 | 0.06% | 4.911..4.917 | stable | 4.910 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.111 | 0.007 | 5.87% | 0.106..0.118 | stable | 0.104 |
| `native_mem_max_bytes.method_map` | 3 | 0.279 | 0.004 | 1.42% | 0.275..0.282 | stable | 0.272 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.000 | 2.68% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_observed_total_bytes` | 3 | 24.731 | 0.011 | 0.05% | 24.720..24.742 | stable | 24.722 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.569 | 0.000 | 0.01% | 3.569..3.569 | stable | 3.569 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.111 | 0.007 | 5.87% | 0.106..0.118 | stable | 0.104 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.279 | 0.004 | 1.42% | 0.275..0.282 | stable | 0.272 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.008 | 0.000 | 2.68% | 0.008..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.057 | 0.002 | 3.53% | 0.055..0.059 | stable | 0.058 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.868 | 0.019 | 0.39% | stable | 4.587 | 0.281 |
| internal | 3 | 1.010 | 0.006 | 0.55% | stable | 0.638 | 0.373 |
| thread | 3 | 1.734 | 0.121 | 7.00% | noisy | 1.644 | 0.090 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 22.903 | 1.288 | 5.62% | noisy | 22.386 | 0.517 |
| metaspace | 3 | 11.495 | 0.036 | 0.31% | stable | 11.266 | 0.229 |
| arena_chunk | 3 | 1.292 | 1.036 | 80.19% | noisy | 0.002 | 1.290 |
| native_memory_tracking | 3 | 1.544 | 0.048 | 3.10% | stable | 1.374 | 0.170 |
| total | 3 | 720.605 | 12.755 | 1.77% | banded | 708.855 | 11.750 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 656.656 | 9.097 |
| counters | RssAnon | 3 | 629.923 | 9.191 |
| nmt | VmRSS | 3 | 662.676 | 9.220 |
| nmt | RssAnon | 3 | 636.078 | 9.178 |
| noprof | VmRSS | 1 | 644.301 | 0.000 |
| noprof | RssAnon | 1 | 621.758 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.114 | 0.012 | 10.31% | 0.106..0.127 | stable | 0.108 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.159 | 0.013 | 8.16% | 0.151..0.174 | stable | 0.154 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 15.65% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.413 | 0.131 | 0.50% | 26.311..26.561 | stable | 26.363 |
| `native_mem_live_bytes.calltrace` | 3 | 4.451 | 0.024 | 0.55% | 4.423..4.469 | stable | 4.440 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.345 | 0.035 | 10.27% | 0.324..0.386 | stable | 0.331 |
| `native_mem_live_bytes.method_map` | 3 | 0.954 | 0.078 | 8.16% | 0.903..1.043 | noisy | 0.926 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.008 | 0.001 | 11.59% | 0.008..0.010 | stable | 0.009 |
| `native_mem_live_bytes.thread_local` | 3 | 0.068 | 0.004 | 5.33% | 0.065..0.072 | stable | 0.070 |
| `native_mem_max_bytes` | 3 | 28.341 | 0.286 | 1.01% | 28.174..28.670 | banded | 28.209 |
| `native_mem_max_bytes.calltrace` | 3 | 6.367 | 0.177 | 2.78% | 6.258..6.571 | banded | 6.276 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.345 | 0.035 | 10.27% | 0.324..0.386 | stable | 0.331 |
| `native_mem_max_bytes.method_map` | 3 | 0.954 | 0.078 | 8.16% | 0.903..1.043 | noisy | 0.926 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.001 | 11.59% | 0.008..0.010 | stable | 0.009 |
| `native_mem_max_bytes.thread_local` | 3 | 0.071 | 0.005 | 6.45% | 0.066..0.076 | stable | 0.073 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.413 | 0.131 | 0.50% | 26.311..26.561 | stable | 26.363 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.730 | 0.012 | 0.31% | 3.723..3.744 | stable | 3.724 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.345 | 0.035 | 10.27% | 0.324..0.386 | stable | 0.331 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.954 | 0.078 | 8.16% | 0.903..1.043 | noisy | 0.926 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 15.96% | 0.006..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.063 | 0.003 | 4.17% | 0.062..0.066 | stable | 0.065 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.419 | 0.004 | 0.01% | stable | 65.480 | 2.938 |
| internal | 3 | 6.793 | 0.007 | 0.10% | stable | 3.591 | 3.202 |
| thread | 3 | 2.183 | 0.147 | 6.74% | noisy | 2.188 | -0.005 |
| symbol | 3 | 5.877 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 65.876 | 1.173 | 1.78% | banded | 59.028 | 6.848 |
| metaspace | 3 | 117.126 | 2.242 | 1.91% | banded | 115.929 | 1.198 |
| arena_chunk | 3 | 3.833 | 0.063 | 1.65% | banded | 4.087 | -0.254 |
| native_memory_tracking | 3 | 12.206 | 0.122 | 1.00% | banded | 10.106 | 2.100 |
| total | 3 | 959.205 | 17.523 | 1.83% | banded | 940.420 | 18.785 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 904.797 | 6.517 |
| counters | RssAnon | 3 | 877.798 | 6.540 |
| nmt | VmRSS | 3 | 939.345 | 13.905 |
| nmt | RssAnon | 3 | 912.457 | 13.840 |
| noprof | VmRSS | 1 | 887.219 | 0.000 |
| noprof | RssAnon | 1 | 864.805 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 0.90% | 0.087..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.001 | 0.82% | 0.073..0.074 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 1.25% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.064 | 0.020 | 0.08% | 26.049..26.087 | stable | 26.048 |
| `native_mem_live_bytes.calltrace` | 3 | 4.344 | 0.018 | 0.42% | 4.330..4.365 | stable | 4.320 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.131 | 0.001 | 0.64% | 0.130..0.132 | stable | 0.138 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.440 | 0.004 | 0.82% | 0.437..0.444 | stable | 0.442 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.000 | 1.37% | 0.006..0.006 | stable | 0.005 |
| `native_mem_live_bytes.thread_local` | 3 | 0.055 | 0.001 | 1.39% | 0.054..0.056 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.656 | 0.018 | 0.06% | 27.635..27.666 | stable | 27.669 |
| `native_mem_max_bytes.calltrace` | 3 | 5.914 | 0.015 | 0.25% | 5.897..5.924 | stable | 5.919 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.131 | 0.001 | 0.64% | 0.130..0.132 | stable | 0.138 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.440 | 0.004 | 0.82% | 0.437..0.444 | stable | 0.442 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.011 | 0.001 | 7.70% | 0.010..0.012 | stable | 0.011 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.064 | 0.020 | 0.08% | 26.049..26.087 | stable | 26.048 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.03% | 3.693..3.695 | stable | 3.695 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.131 | 0.001 | 0.64% | 0.130..0.132 | stable | 0.138 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.440 | 0.004 | 0.82% | 0.437..0.444 | stable | 0.442 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.011 | 0.001 | 7.70% | 0.010..0.012 | stable | 0.011 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.060 | 0.000 | 0.74% | 0.060..0.060 | stable | 0.059 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.857 | 0.014 | 0.29% | stable | 4.588 | 0.269 |
| internal | 3 | 1.046 | 0.009 | 0.89% | stable | 0.638 | 0.408 |
| thread | 3 | 1.687 | 0.114 | 6.73% | noisy | 1.729 | -0.043 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 22.087 | 1.111 | 5.03% | noisy | 22.583 | -0.496 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 1.292 | 1.036 | 80.19% | noisy | 0.002 | 1.290 |
| native_memory_tracking | 3 | 1.520 | 0.037 | 2.47% | stable | 1.378 | 0.142 |
| total | 3 | 719.670 | 13.691 | 1.90% | banded | 703.036 | 16.634 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 658.747 | 8.416 |
| counters | RssAnon | 3 | 631.775 | 8.424 |
| nmt | VmRSS | 3 | 656.932 | 3.545 |
| nmt | RssAnon | 3 | 630.312 | 3.568 |
| noprof | VmRSS | 1 | 644.039 | 0.000 |
| noprof | RssAnon | 1 | 621.562 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 16.43% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 9.55% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 1.65% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.134 | 0.002 | 0.01% | 22.132..22.135 | stable | 22.138 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.00% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.17% | 0.005..0.008 | stable | 0.009 |
| `native_mem_live_bytes.method_map` | 3 | 0.005 | 0.001 | 10.64% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.031 | 0.001 | 2.47% | 0.030..0.032 | stable | 0.031 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.165 | 0.004 | 0.02% | 23.161..23.169 | stable | 23.166 |
| `native_mem_max_bytes.calltrace` | 3 | 4.553 | 0.001 | 0.01% | 4.553..4.554 | stable | 4.553 |
| `native_mem_max_bytes.dictionary` | 3 | 4.569 | 0.005 | 0.10% | 4.564..4.572 | stable | 4.566 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.17% | 0.005..0.008 | stable | 0.009 |
| `native_mem_max_bytes.method_map` | 3 | 0.005 | 0.001 | 10.64% | 0.005..0.006 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.031 | 0.001 | 2.45% | 0.031..0.032 | stable | 0.031 |
| `native_mem_max_bytes.thread_local` | 3 | 0.208 | 0.000 | 0.00% | 0.208..0.208 | stable | 0.208 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.134 | 0.002 | 0.01% | 22.132..22.135 | stable | 22.138 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.17% | 0.005..0.008 | stable | 0.009 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.005 | 0.001 | 10.64% | 0.005..0.006 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.031 | 0.001 | 2.45% | 0.031..0.032 | stable | 0.031 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.393 | 0.003 | 0.80% | stable | 0.278 | 0.115 |
| internal | 3 | 0.760 | 0.012 | 1.53% | stable | 0.593 | 0.168 |
| thread | 3 | 22.244 | 0.114 | 0.51% | stable | 22.144 | 0.101 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.444 | 0.000 | 0.00% | stable | 7.437 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.008 | 0.001 | 6.93% | stable | 0.008 | 0.000 |
| native_memory_tracking | 3 | 0.346 | 0.007 | 2.08% | stable | 0.295 | 0.051 |
| total | 3 | 690.787 | 23.296 | 3.37% | banded | 670.969 | 19.818 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 615.848 | 0.771 |
| counters | RssAnon | 3 | 589.353 | 0.642 |
| nmt | VmRSS | 3 | 616.074 | 1.002 |
| nmt | RssAnon | 3 | 589.682 | 1.012 |
| noprof | VmRSS | 1 | 590.918 | 0.000 |
| noprof | RssAnon | 1 | 569.543 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.055 | 0.002 | 4.39% | 0.053..0.057 | stable | 0.054 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.003 | 4.23% | 0.072..0.078 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.90% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 23.333 | 0.049 | 0.21% | 23.277..23.368 | stable | 23.289 |
| `native_mem_live_bytes.calltrace` | 3 | 4.340 | 0.027 | 0.61% | 4.310..4.361 | stable | 4.303 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.135 | 0.008 | 5.90% | 0.128..0.144 | stable | 0.131 |
| `native_mem_live_bytes.method_map` | 3 | 0.453 | 0.019 | 4.23% | 0.431..0.467 | stable | 0.442 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.001 | 18.43% | 0.005..0.007 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.062 | 0.002 | 2.58% | 0.060..0.063 | stable | 0.063 |
| `native_mem_max_bytes` | 3 | 24.980 | 0.052 | 0.21% | 24.922..25.022 | stable | 24.957 |
| `native_mem_max_bytes.calltrace` | 3 | 5.424 | 0.033 | 0.60% | 5.390..5.455 | stable | 5.411 |
| `native_mem_max_bytes.dictionary` | 3 | 5.094 | 0.001 | 0.02% | 5.094..5.096 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.135 | 0.008 | 5.90% | 0.128..0.144 | stable | 0.131 |
| `native_mem_max_bytes.method_map` | 3 | 0.453 | 0.019 | 4.23% | 0.431..0.467 | stable | 0.442 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.002 | 19.21% | 0.007..0.010 | stable | 0.009 |
| `native_mem_max_bytes.thread_local` | 3 | 0.073 | 0.003 | 4.37% | 0.070..0.076 | stable | 0.074 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.333 | 0.049 | 0.21% | 23.277..23.368 | stable | 23.289 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.625 | 0.002 | 0.07% | 3.623..3.628 | stable | 3.624 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.135 | 0.008 | 5.90% | 0.128..0.144 | stable | 0.131 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.453 | 0.019 | 4.23% | 0.431..0.467 | stable | 0.442 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.009 | 0.002 | 19.21% | 0.007..0.010 | stable | 0.009 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.065 | 0.002 | 3.56% | 0.063..0.068 | stable | 0.066 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.729 | 0.002 | 0.03% | stable | 8.265 | 0.464 |
| internal | 3 | 1.434 | 0.005 | 0.32% | stable | 0.827 | 0.607 |
| thread | 3 | 1.916 | 0.108 | 5.65% | noisy | 1.612 | 0.304 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 53.406 | 0.326 | 0.61% | stable | 46.280 | 7.126 |
| metaspace | 3 | 21.945 | 0.005 | 0.02% | stable | 21.753 | 0.192 |
| arena_chunk | 3 | 0.925 | 0.809 | 87.40% | noisy | 0.003 | 0.922 |
| native_memory_tracking | 3 | 2.644 | 0.004 | 0.14% | stable | 2.321 | 0.323 |
| total | 3 | 759.835 | 16.122 | 2.12% | banded | 722.754 | 37.081 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 715.751 | 5.479 |
| counters | RssAnon | 3 | 688.967 | 5.268 |
| nmt | VmRSS | 3 | 723.794 | 3.211 |
| nmt | RssAnon | 3 | 696.854 | 3.099 |
| noprof | VmRSS | 1 | 679.840 | 0.000 |
| noprof | RssAnon | 1 | 657.559 | 0.000 |
