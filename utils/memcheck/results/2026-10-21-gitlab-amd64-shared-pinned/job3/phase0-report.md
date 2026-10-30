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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 0.57% | 0.021..0.021 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.042 | 0.000 | 0.99% | 0.041..0.042 | stable | 0.041 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 13.29% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.718 | 0.018 | 0.07% | 24.701..24.737 | stable | 24.701 |
| `native_mem_live_bytes.calltrace` | 3 | 3.727 | 0.013 | 0.35% | 3.714..3.740 | stable | 3.713 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.099 | 0.004 | 4.50% | 0.094..0.103 | stable | 0.098 |
| `native_mem_live_bytes.method_map` | 3 | 0.250 | 0.002 | 0.99% | 0.247..0.252 | stable | 0.247 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.869 | 0.006 | 0.02% | 25.864..25.876 | stable | 25.861 |
| `native_mem_max_bytes.calltrace` | 3 | 4.877 | 0.002 | 0.04% | 4.875..4.878 | stable | 4.873 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.099 | 0.004 | 4.50% | 0.094..0.103 | stable | 0.098 |
| `native_mem_max_bytes.method_map` | 3 | 0.250 | 0.002 | 0.99% | 0.247..0.252 | stable | 0.247 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 15.46% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_observed_total_bytes` | 3 | 24.718 | 0.018 | 0.07% | 24.701..24.737 | stable | 24.701 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.000 | 0.00% | 3.567..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.099 | 0.004 | 4.50% | 0.094..0.103 | stable | 0.098 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.250 | 0.002 | 0.99% | 0.247..0.252 | stable | 0.247 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 15.46% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.820 | 0.002 | 0.04% | stable | 4.526 | 0.294 |
| internal | 3 | 0.891 | 0.048 | 5.41% | stable | 0.504 | 0.387 |
| thread | 3 | 0.828 | 0.045 | 5.45% | stable | 0.801 | 0.027 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 17.520 | 0.095 | 0.54% | stable | 16.739 | 0.781 |
| metaspace | 3 | 11.495 | 0.036 | 0.31% | stable | 11.266 | 0.229 |
| arena_chunk | 3 | 0.432 | 0.018 | 4.17% | stable | 0.391 | 0.042 |
| native_memory_tracking | 3 | 1.214 | 0.124 | 10.22% | noisy | 0.948 | 0.266 |
| total | 3 | 581.554 | 27.108 | 4.66% | banded | 564.024 | 17.530 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 622.233 | 6.876 |
| counters | RssAnon | 3 | 596.387 | 6.235 |
| nmt | VmRSS | 3 | 624.279 | 7.125 |
| nmt | RssAnon | 3 | 598.538 | 6.526 |
| noprof | VmRSS | 1 | 591.898 | 0.000 |
| noprof | RssAnon | 1 | 570.828 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.117 | 0.003 | 2.42% | 0.115..0.120 | stable | 0.118 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.163 | 0.004 | 2.61% | 0.158..0.166 | stable | 0.164 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 15.06% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.440 | 0.083 | 0.31% | 26.344..26.495 | stable | 26.475 |
| `native_mem_live_bytes.calltrace` | 3 | 4.458 | 0.046 | 1.03% | 4.406..4.490 | stable | 4.481 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.362 | 0.014 | 3.91% | 0.347..0.375 | stable | 0.365 |
| `native_mem_live_bytes.method_map` | 3 | 0.977 | 0.026 | 2.61% | 0.949..0.999 | stable | 0.985 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 28.467 | 0.097 | 0.34% | 28.366..28.559 | stable | 28.495 |
| `native_mem_max_bytes.calltrace` | 3 | 6.476 | 0.058 | 0.89% | 6.419..6.534 | stable | 6.493 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.362 | 0.014 | 3.91% | 0.347..0.375 | stable | 0.365 |
| `native_mem_max_bytes.method_map` | 3 | 0.977 | 0.026 | 2.61% | 0.949..0.999 | stable | 0.985 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.440 | 0.083 | 0.31% | 26.344..26.495 | stable | 26.475 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.734 | 0.003 | 0.08% | 3.731..3.737 | stable | 3.735 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.362 | 0.014 | 3.91% | 0.347..0.375 | stable | 0.365 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.977 | 0.026 | 2.61% | 0.949..0.999 | stable | 0.985 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.460 | 2.939 |
| internal | 3 | 6.723 | 0.043 | 0.64% | stable | 3.446 | 3.277 |
| thread | 3 | 0.836 | 0.052 | 6.23% | stable | 0.805 | 0.031 |
| symbol | 3 | 5.877 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 58.067 | 0.772 | 1.33% | banded | 52.285 | 5.782 |
| metaspace | 3 | 114.479 | 0.000 | 0.00% | stable | 116.313 | -1.834 |
| arena_chunk | 3 | 0.382 | 0.344 | 90.16% | noisy | 0.671 | -0.289 |
| native_memory_tracking | 3 | 11.497 | 0.445 | 3.87% | banded | 9.255 | 2.242 |
| total | 3 | 817.169 | 29.262 | 3.58% | banded | 788.905 | 28.263 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 863.464 | 10.467 |
| counters | RssAnon | 3 | 837.320 | 9.695 |
| nmt | VmRSS | 3 | 875.384 | 10.601 |
| nmt | RssAnon | 3 | 849.137 | 10.013 |
| noprof | VmRSS | 1 | 827.121 | 0.000 |
| noprof | RssAnon | 1 | 805.785 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.089 | 0.000 | 0.53% | 0.089..0.090 | stable | 0.089 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.074 | 0.001 | 0.99% | 0.073..0.075 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 11.55% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.346 | 0.028 | 0.11% | 26.314..26.365 | stable | 26.344 |
| `native_mem_live_bytes.calltrace` | 3 | 4.628 | 0.026 | 0.56% | 4.599..4.646 | stable | 4.626 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.142 | 0.008 | 5.95% | 0.133..0.149 | stable | 0.143 |
| `native_mem_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.489 |
| `native_mem_live_bytes.method_map` | 3 | 0.444 | 0.004 | 0.99% | 0.439..0.448 | stable | 0.441 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 16.19% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.709 | 0.014 | 0.05% | 27.693..27.719 | stable | 27.710 |
| `native_mem_max_bytes.calltrace` | 3 | 5.982 | 0.011 | 0.19% | 5.969..5.991 | stable | 5.985 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.142 | 0.008 | 5.95% | 0.133..0.149 | stable | 0.143 |
| `native_mem_max_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.489 |
| `native_mem_max_bytes.method_map` | 3 | 0.444 | 0.004 | 0.99% | 0.439..0.448 | stable | 0.441 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 16.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.346 | 0.028 | 0.11% | 26.314..26.365 | stable | 26.344 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.696 | 0.001 | 0.02% | 3.695..3.696 | stable | 3.696 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.142 | 0.008 | 5.95% | 0.133..0.149 | stable | 0.143 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.489 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.444 | 0.004 | 0.99% | 0.439..0.448 | stable | 0.441 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 16.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.820 | 0.001 | 0.03% | stable | 4.522 | 0.298 |
| internal | 3 | 0.940 | 0.043 | 4.62% | stable | 0.504 | 0.436 |
| thread | 3 | 0.834 | 0.046 | 5.55% | stable | 0.801 | 0.034 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.538 | 0.169 | 0.96% | stable | 16.385 | 1.153 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.432 | 0.018 | 4.12% | stable | 0.391 | 0.041 |
| native_memory_tracking | 3 | 1.224 | 0.122 | 9.95% | noisy | 0.937 | 0.287 |
| total | 3 | 581.616 | 26.874 | 4.62% | banded | 563.651 | 17.965 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 624.302 | 6.975 |
| counters | RssAnon | 3 | 598.298 | 6.327 |
| nmt | VmRSS | 3 | 625.702 | 7.357 |
| nmt | RssAnon | 3 | 599.784 | 6.564 |
| noprof | VmRSS | 1 | 591.430 | 0.000 |
| noprof | RssAnon | 1 | 570.074 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 11.10% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.002 | 0.000 | 24.84% | 0.001..0.002 | stable | 0.002 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.73% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.140 | 0.005 | 0.02% | 22.135..22.145 | stable | 22.144 |
| `native_mem_live_bytes.calltrace` | 3 | 3.547 | 0.001 | 0.02% | 3.546..3.548 | stable | 3.547 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.012 | 0.004 | 32.75% | 0.008..0.016 | stable | 0.014 |
| `native_mem_live_bytes.method_map` | 3 | 0.009 | 0.002 | 25.49% | 0.007..0.012 | stable | 0.010 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.14% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.202 | 0.032 | 0.14% | 23.169..23.233 | stable | 23.201 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.000 | 0.01% | 4.553..4.554 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.599 | 0.026 | 0.56% | 4.573..4.624 | stable | 4.595 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.012 | 0.004 | 32.75% | 0.008..0.016 | stable | 0.014 |
| `native_mem_max_bytes.method_map` | 3 | 0.009 | 0.002 | 25.49% | 0.007..0.012 | stable | 0.010 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.13% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.140 | 0.005 | 0.02% | 22.135..22.145 | stable | 22.144 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.012 | 0.004 | 32.75% | 0.008..0.016 | stable | 0.014 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.009 | 0.002 | 25.49% | 0.007..0.012 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 1.13% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.382 | 0.001 | 0.30% | stable | 0.271 | 0.110 |
| internal | 3 | 0.705 | 0.017 | 2.46% | stable | 0.565 | 0.139 |
| thread | 3 | 21.779 | 0.054 | 0.25% | stable | 21.833 | -0.054 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.01% | stable | 7.434 | 0.006 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.271 | 0.045 | 16.63% | stable | 0.278 | -0.007 |
| total | 3 | 576.095 | 29.042 | 5.04% | noisy | 609.043 | -32.948 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 605.568 | 6.160 |
| counters | RssAnon | 3 | 580.004 | 5.423 |
| nmt | VmRSS | 3 | 605.876 | 6.360 |
| nmt | RssAnon | 3 | 580.301 | 5.639 |
| noprof | VmRSS | 1 | 588.695 | 0.000 |
| noprof | RssAnon | 1 | 567.336 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.058 | 0.001 | 0.91% | 0.058..0.059 | stable | 0.061 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.085 | 0.001 | 1.39% | 0.084..0.086 | stable | 0.086 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 3.94% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.376 | 0.017 | 0.07% | 23.360..23.394 | stable | 23.379 |
| `native_mem_live_bytes.calltrace` | 3 | 4.294 | 0.002 | 0.05% | 4.292..4.295 | stable | 4.293 |
| `native_mem_live_bytes.dictionary` | 3 | 4.565 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.170 | 0.002 | 1.32% | 0.169..0.173 | stable | 0.172 |
| `native_mem_live_bytes.method_map` | 3 | 0.507 | 0.007 | 1.39% | 0.503..0.515 | stable | 0.514 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.161 | 0.025 | 0.10% | 25.138..25.187 | stable | 25.200 |
| `native_mem_max_bytes.calltrace` | 3 | 5.520 | 0.006 | 0.11% | 5.514..5.526 | stable | 5.555 |
| `native_mem_max_bytes.dictionary` | 3 | 5.115 | 0.011 | 0.21% | 5.103..5.124 | stable | 5.109 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.170 | 0.002 | 1.32% | 0.169..0.173 | stable | 0.172 |
| `native_mem_max_bytes.method_map` | 3 | 0.507 | 0.007 | 1.39% | 0.503..0.515 | stable | 0.514 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.376 | 0.017 | 0.07% | 23.360..23.394 | stable | 23.379 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.628 | 0.001 | 0.01% | 3.628..3.629 | stable | 3.631 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.561 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.170 | 0.002 | 1.32% | 0.169..0.173 | stable | 0.172 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.507 | 0.007 | 1.39% | 0.503..0.515 | stable | 0.514 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.710 | 0.000 | 0.00% | stable | 8.252 | 0.458 |
| internal | 3 | 1.327 | 0.003 | 0.21% | stable | 0.698 | 0.629 |
| thread | 3 | 0.798 | 0.000 | 0.00% | stable | 0.797 | 0.001 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 24.875 | 4.441 | 17.85% | noisy | 21.297 | 3.578 |
| metaspace | 3 | 21.951 | 0.000 | 0.00% | stable | 21.753 | 0.198 |
| arena_chunk | 3 | 0.616 | 0.339 | 55.07% | noisy | 0.636 | -0.020 |
| native_memory_tracking | 3 | 2.001 | 0.047 | 2.36% | stable | 1.674 | 0.327 |
| total | 3 | 590.065 | 4.634 | 0.79% | stable | 584.882 | 5.183 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 645.980 | 2.396 |
| counters | RssAnon | 3 | 620.323 | 2.480 |
| nmt | VmRSS | 3 | 648.517 | 4.799 |
| nmt | RssAnon | 3 | 622.936 | 4.795 |
| noprof | VmRSS | 1 | 614.867 | 0.000 |
| noprof | RssAnon | 1 | 593.531 | 0.000 |
