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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.022 | 0.001 | 2.33% | 0.022..0.023 | stable | 0.022 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.044 | 0.001 | 2.38% | 0.043..0.045 | stable | 0.043 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.09% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.729 | 0.004 | 0.02% | 24.726..24.734 | stable | 24.726 |
| `native_mem_live_bytes.calltrace` | 3 | 3.721 | 0.007 | 0.19% | 3.713..3.726 | stable | 3.717 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.101 | 0.001 | 0.87% | 0.100..0.102 | stable | 0.106 |
| `native_mem_live_bytes.method_map` | 3 | 0.263 | 0.006 | 2.38% | 0.257..0.269 | stable | 0.259 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.06% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.904 | 0.013 | 0.05% | 25.890..25.915 | stable | 25.897 |
| `native_mem_max_bytes.calltrace` | 3 | 4.894 | 0.007 | 0.15% | 4.886..4.901 | stable | 4.887 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.101 | 0.001 | 0.87% | 0.100..0.102 | stable | 0.106 |
| `native_mem_max_bytes.method_map` | 3 | 0.263 | 0.006 | 2.38% | 0.257..0.269 | stable | 0.259 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.82% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.729 | 0.004 | 0.02% | 24.726..24.734 | stable | 24.726 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.568 | 0.001 | 0.02% | 3.567..3.568 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.101 | 0.001 | 0.87% | 0.100..0.102 | stable | 0.106 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.263 | 0.006 | 2.38% | 0.257..0.269 | stable | 0.259 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.82% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.001 | 0.01% | stable | 4.526 | 0.297 |
| internal | 3 | 0.956 | 0.009 | 0.89% | stable | 0.588 | 0.368 |
| thread | 3 | 0.920 | 0.000 | 0.00% | stable | 0.919 | 0.001 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.534 | 0.078 | 0.42% | stable | 16.915 | 1.619 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.105 | 0.019 | 17.64% | stable | 0.126 | -0.021 |
| native_memory_tracking | 3 | 1.424 | 0.003 | 0.22% | stable | 1.219 | 0.205 |
| total | 3 | 617.652 | 0.071 | 0.01% | stable | 614.963 | 2.689 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 633.266 | 0.375 |
| counters | RssAnon | 3 | 606.529 | 0.294 |
| nmt | VmRSS | 3 | 634.853 | 0.102 |
| nmt | RssAnon | 3 | 608.142 | 0.226 |
| noprof | VmRSS | 1 | 605.242 | 0.000 |
| noprof | RssAnon | 1 | 583.031 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.108 | 0.002 | 2.23% | 0.105..0.110 | stable | 0.109 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.153 | 0.003 | 1.84% | 0.151..0.156 | stable | 0.153 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.65% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.299 | 0.033 | 0.12% | 26.279..26.337 | stable | 26.315 |
| `native_mem_live_bytes.calltrace` | 3 | 4.406 | 0.015 | 0.33% | 4.390..4.417 | stable | 4.415 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.329 | 0.009 | 2.76% | 0.319..0.337 | stable | 0.334 |
| `native_mem_live_bytes.method_map` | 3 | 0.919 | 0.017 | 1.82% | 0.906..0.938 | stable | 0.920 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.42% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.158 | 0.058 | 0.21% | 28.102..28.218 | stable | 28.193 |
| `native_mem_max_bytes.calltrace` | 3 | 6.258 | 0.033 | 0.52% | 6.225..6.290 | stable | 6.286 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.329 | 0.009 | 2.76% | 0.319..0.337 | stable | 0.334 |
| `native_mem_max_bytes.method_map` | 3 | 0.919 | 0.017 | 1.82% | 0.906..0.938 | stable | 0.920 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.42% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.299 | 0.033 | 0.12% | 26.279..26.337 | stable | 26.315 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.724 | 0.002 | 0.06% | 3.722..3.726 | stable | 3.725 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.329 | 0.009 | 2.76% | 0.319..0.337 | stable | 0.334 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.919 | 0.017 | 1.82% | 0.906..0.938 | stable | 0.920 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.400 | 0.000 | 0.00% | stable | 65.461 | 2.939 |
| internal | 3 | 6.735 | 0.013 | 0.19% | stable | 3.528 | 3.207 |
| thread | 3 | 0.930 | 0.002 | 0.24% | stable | 0.931 | -0.000 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 59.374 | 0.362 | 0.61% | stable | 52.296 | 7.078 |
| metaspace | 3 | 116.482 | 0.403 | 0.35% | stable | 116.889 | -0.407 |
| arena_chunk | 3 | 0.523 | 0.163 | 31.05% | noisy | 0.702 | -0.179 |
| native_memory_tracking | 3 | 12.054 | 0.017 | 0.14% | stable | 9.995 | 2.059 |
| total | 3 | 857.217 | 0.269 | 0.03% | stable | 842.304 | 14.914 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 879.240 | 6.173 |
| counters | RssAnon | 3 | 852.357 | 6.028 |
| nmt | VmRSS | 3 | 887.694 | 1.984 |
| nmt | RssAnon | 3 | 860.786 | 1.870 |
| noprof | VmRSS | 1 | 849.164 | 0.000 |
| noprof | RssAnon | 1 | 826.809 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.087 | 0.001 | 1.28% | 0.086..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.000 | 0.44% | 0.073..0.074 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 3.07% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.175 | 0.030 | 0.11% | 26.148..26.207 | stable | 26.168 |
| `native_mem_live_bytes.calltrace` | 3 | 4.455 | 0.034 | 0.75% | 4.421..4.488 | stable | 4.441 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.137 | 0.007 | 4.98% | 0.133..0.145 | stable | 0.140 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.439 | 0.002 | 0.45% | 0.437..0.441 | stable | 0.443 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.97% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.663 | 0.011 | 0.04% | 27.650..27.671 | stable | 27.674 |
| `native_mem_max_bytes.calltrace` | 3 | 5.932 | 0.013 | 0.22% | 5.921..5.946 | stable | 5.938 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.137 | 0.007 | 4.98% | 0.133..0.145 | stable | 0.140 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.439 | 0.002 | 0.45% | 0.437..0.441 | stable | 0.443 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 5.37% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.175 | 0.030 | 0.11% | 26.148..26.207 | stable | 26.168 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.02% | 3.693..3.695 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.137 | 0.007 | 4.98% | 0.133..0.145 | stable | 0.140 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.439 | 0.002 | 0.45% | 0.437..0.441 | stable | 0.443 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 5.37% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.80% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.824 | 0.001 | 0.02% | stable | 4.526 | 0.298 |
| internal | 3 | 0.993 | 0.004 | 0.40% | stable | 0.587 | 0.406 |
| thread | 3 | 0.938 | 0.027 | 2.89% | stable | 0.919 | 0.019 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.579 | 0.037 | 0.20% | stable | 16.913 | 1.666 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.376 | 0.383 | 101.88% | noisy | 0.781 | -0.406 |
| native_memory_tracking | 3 | 1.433 | 0.001 | 0.04% | stable | 1.220 | 0.213 |
| total | 3 | 618.051 | 0.432 | 0.07% | stable | 615.615 | 2.436 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 634.223 | 0.729 |
| counters | RssAnon | 3 | 607.275 | 0.705 |
| nmt | VmRSS | 3 | 637.034 | 0.238 |
| nmt | RssAnon | 3 | 610.151 | 0.213 |
| noprof | VmRSS | 1 | 604.070 | 0.000 |
| noprof | RssAnon | 1 | 581.695 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 14.78% | 0.000..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 26.84% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.00% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.132 | 0.003 | 0.01% | 22.129..22.135 | stable | 22.133 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.35% | 0.005..0.008 | stable | 0.006 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.002 | 27.30% | 0.004..0.007 | stable | 0.007 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.166 | 0.013 | 0.06% | 23.154..23.180 | stable | 23.162 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.02% | 4.553..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.572 | 0.009 | 0.19% | 4.564..4.582 | stable | 4.567 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.35% | 0.005..0.008 | stable | 0.006 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.002 | 27.30% | 0.004..0.007 | stable | 0.007 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.132 | 0.003 | 0.01% | 22.130..22.135 | stable | 22.133 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.006 | 0.002 | 33.35% | 0.005..0.008 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.002 | 27.30% | 0.004..0.007 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 3 | 0.721 | 0.001 | 0.08% | stable | 0.564 | 0.157 |
| thread | 3 | 21.839 | 0.002 | 0.01% | stable | 21.833 | 0.006 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.01% | stable | 7.431 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.330 | 0.003 | 0.90% | stable | 0.278 | 0.052 |
| total | 3 | 610.781 | 0.552 | 0.09% | stable | 609.217 | 1.564 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 613.271 | 0.254 |
| counters | RssAnon | 3 | 586.828 | 0.299 |
| nmt | VmRSS | 3 | 613.737 | 0.157 |
| nmt | RssAnon | 3 | 587.366 | 0.303 |
| noprof | VmRSS | 1 | 589.047 | 0.000 |
| noprof | RssAnon | 1 | 567.574 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.054 | 0.000 | 0.37% | 0.054..0.054 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.078 | 0.001 | 0.81% | 0.078..0.079 | stable | 0.080 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.39% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.281 | 0.012 | 0.05% | 23.268..23.291 | stable | 23.280 |
| `native_mem_live_bytes.calltrace` | 3 | 4.265 | 0.011 | 0.27% | 4.255..4.277 | stable | 4.261 |
| `native_mem_live_bytes.dictionary` | 3 | 4.559 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.146 | 0.006 | 4.28% | 0.140..0.152 | stable | 0.146 |
| `native_mem_live_bytes.method_map` | 3 | 0.470 | 0.004 | 0.81% | 0.466..0.473 | stable | 0.478 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.09% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.952 | 0.016 | 0.06% | 24.943..24.970 | stable | 24.968 |
| `native_mem_max_bytes.calltrace` | 3 | 5.386 | 0.001 | 0.02% | 5.385..5.388 | stable | 5.397 |
| `native_mem_max_bytes.dictionary` | 3 | 5.100 | 0.008 | 0.16% | 5.094..5.109 | stable | 5.097 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.146 | 0.006 | 4.28% | 0.140..0.152 | stable | 0.146 |
| `native_mem_max_bytes.method_map` | 3 | 0.470 | 0.004 | 0.81% | 0.466..0.473 | stable | 0.478 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.60% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.281 | 0.012 | 0.05% | 23.268..23.291 | stable | 23.280 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.000 | 0.01% | 3.624..3.624 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.557 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.146 | 0.006 | 4.28% | 0.140..0.152 | stable | 0.146 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.470 | 0.004 | 0.81% | 0.466..0.473 | stable | 0.478 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.60% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.000 | 0.00% | stable | 8.254 | 0.459 |
| internal | 3 | 1.382 | 0.004 | 0.29% | stable | 0.780 | 0.602 |
| thread | 3 | 0.954 | 0.019 | 2.01% | stable | 0.976 | -0.022 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 30.508 | 0.968 | 3.17% | banded | 24.552 | 5.956 |
| metaspace | 3 | 21.996 | 0.039 | 0.18% | stable | 21.762 | 0.234 |
| arena_chunk | 3 | 1.074 | 0.467 | 43.51% | noisy | 1.374 | -0.300 |
| native_memory_tracking | 3 | 2.388 | 0.017 | 0.72% | stable | 2.041 | 0.347 |
| total | 3 | 647.714 | 1.029 | 0.16% | stable | 640.104 | 7.610 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 676.520 | 3.992 |
| counters | RssAnon | 3 | 649.605 | 3.978 |
| nmt | VmRSS | 3 | 678.898 | 5.599 |
| nmt | RssAnon | 3 | 652.072 | 5.599 |
| noprof | VmRSS | 1 | 640.004 | 0.000 |
| noprof | RssAnon | 1 | 617.664 | 0.000 |
