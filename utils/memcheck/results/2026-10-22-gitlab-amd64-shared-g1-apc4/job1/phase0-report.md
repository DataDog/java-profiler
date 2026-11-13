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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 1.83% | 0.021..0.022 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.042 | 0.001 | 2.02% | 0.041..0.043 | stable | 0.042 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.55% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.725 | 0.013 | 0.05% | 24.715..24.740 | stable | 24.718 |
| `native_mem_live_bytes.calltrace` | 3 | 3.734 | 0.012 | 0.32% | 3.725..3.747 | stable | 3.723 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.097 | 0.000 | 0.46% | 0.097..0.097 | stable | 0.099 |
| `native_mem_live_bytes.method_map` | 3 | 0.251 | 0.005 | 2.02% | 0.245..0.255 | stable | 0.252 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.01% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.874 | 0.010 | 0.04% | 25.863..25.883 | stable | 25.878 |
| `native_mem_max_bytes.calltrace` | 3 | 4.881 | 0.005 | 0.10% | 4.876..4.886 | stable | 4.882 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.097 | 0.000 | 0.46% | 0.097..0.097 | stable | 0.099 |
| `native_mem_max_bytes.method_map` | 3 | 0.251 | 0.005 | 2.02% | 0.245..0.255 | stable | 0.252 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.66% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.725 | 0.013 | 0.05% | 24.715..24.740 | stable | 24.718 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.000 | 0.01% | 3.567..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.097 | 0.000 | 0.46% | 0.097..0.097 | stable | 0.099 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.251 | 0.005 | 2.02% | 0.245..0.255 | stable | 0.252 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.66% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.000 | 0.00% | stable | 4.528 | 0.295 |
| internal | 3 | 0.949 | 0.006 | 0.66% | stable | 0.588 | 0.361 |
| thread | 3 | 0.934 | 0.024 | 2.54% | stable | 0.919 | 0.015 |
| symbol | 3 | 1.594 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.581 | 0.038 | 0.20% | stable | 16.781 | 1.799 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.344 | 0.432 | 125.52% | noisy | 0.127 | 0.217 |
| native_memory_tracking | 3 | 1.424 | 0.002 | 0.12% | stable | 1.216 | 0.208 |
| total | 3 | 617.944 | 0.434 | 0.07% | stable | 614.819 | 3.125 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 633.785 | 0.884 |
| counters | RssAnon | 3 | 607.169 | 0.949 |
| nmt | VmRSS | 3 | 635.116 | 2.230 |
| nmt | RssAnon | 3 | 608.509 | 2.070 |
| noprof | VmRSS | 1 | 603.906 | 0.000 |
| noprof | RssAnon | 1 | 581.551 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.110 | 0.005 | 4.52% | 0.107..0.116 | stable | 0.107 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.155 | 0.005 | 2.97% | 0.152..0.160 | stable | 0.151 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 7.42% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.306 | 0.057 | 0.22% | 26.250..26.364 | stable | 26.293 |
| `native_mem_live_bytes.calltrace` | 3 | 4.398 | 0.022 | 0.50% | 4.373..4.411 | stable | 4.404 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.335 | 0.012 | 3.68% | 0.323..0.348 | stable | 0.335 |
| `native_mem_live_bytes.method_map` | 3 | 0.929 | 0.028 | 2.97% | 0.910..0.960 | stable | 0.908 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.67% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.221 | 0.108 | 0.38% | 28.152..28.345 | stable | 28.155 |
| `native_mem_max_bytes.calltrace` | 3 | 6.305 | 0.069 | 1.10% | 6.263..6.385 | banded | 6.259 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.335 | 0.012 | 3.68% | 0.323..0.348 | stable | 0.335 |
| `native_mem_max_bytes.method_map` | 3 | 0.929 | 0.028 | 2.97% | 0.910..0.960 | stable | 0.908 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.67% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.306 | 0.057 | 0.22% | 26.250..26.364 | stable | 26.293 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.726 | 0.005 | 0.13% | 3.723..3.732 | stable | 3.723 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.335 | 0.012 | 3.68% | 0.323..0.348 | stable | 0.335 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.929 | 0.028 | 2.97% | 0.910..0.960 | stable | 0.908 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.401 | 0.001 | 0.00% | stable | 65.461 | 2.940 |
| internal | 3 | 6.734 | 0.002 | 0.03% | stable | 3.528 | 3.205 |
| thread | 3 | 0.932 | 0.000 | 0.00% | stable | 0.935 | -0.003 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 58.518 | 0.760 | 1.30% | banded | 52.362 | 6.156 |
| metaspace | 3 | 115.853 | 0.143 | 0.12% | stable | 114.497 | 1.355 |
| arena_chunk | 3 | 0.692 | 0.018 | 2.65% | stable | 0.702 | -0.010 |
| native_memory_tracking | 3 | 12.015 | 0.008 | 0.07% | stable | 9.894 | 2.121 |
| total | 3 | 855.611 | 0.754 | 0.09% | stable | 839.791 | 15.820 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 875.070 | 1.514 |
| counters | RssAnon | 3 | 848.273 | 1.404 |
| nmt | VmRSS | 3 | 889.777 | 0.711 |
| nmt | RssAnon | 3 | 863.073 | 0.651 |
| noprof | VmRSS | 1 | 847.336 | 0.000 |
| noprof | RssAnon | 1 | 824.906 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.086 | 0.000 | 0.21% | 0.086..0.087 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.001 | 1.18% | 0.072..0.074 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 3.01% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.195 | 0.038 | 0.14% | 26.171..26.238 | stable | 26.185 |
| `native_mem_live_bytes.calltrace` | 3 | 4.472 | 0.028 | 0.62% | 4.455..4.504 | stable | 4.471 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.140 | 0.005 | 3.68% | 0.137..0.146 | stable | 0.132 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.439 | 0.005 | 1.18% | 0.434..0.444 | stable | 0.437 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.655 | 0.014 | 0.05% | 27.642..27.669 | stable | 27.666 |
| `native_mem_max_bytes.calltrace` | 3 | 5.922 | 0.004 | 0.07% | 5.917..5.924 | stable | 5.943 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.01% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.140 | 0.005 | 3.68% | 0.137..0.146 | stable | 0.132 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.439 | 0.005 | 1.18% | 0.434..0.444 | stable | 0.437 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 3.10% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.195 | 0.038 | 0.14% | 26.171..26.238 | stable | 26.185 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.693 | 0.000 | 0.01% | 3.693..3.693 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.140 | 0.005 | 3.68% | 0.137..0.146 | stable | 0.132 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.439 | 0.005 | 1.18% | 0.434..0.444 | stable | 0.437 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 3.10% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.824 | 0.001 | 0.01% | stable | 4.528 | 0.295 |
| internal | 3 | 0.985 | 0.004 | 0.40% | stable | 0.587 | 0.398 |
| thread | 3 | 0.952 | 0.028 | 2.96% | stable | 0.919 | 0.034 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.557 | 0.001 | 0.01% | stable | 17.048 | 1.509 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.573 | 0.414 | 72.28% | noisy | 0.127 | 0.446 |
| native_memory_tracking | 3 | 1.433 | 0.001 | 0.04% | stable | 1.222 | 0.212 |
| total | 3 | 618.236 | 0.463 | 0.07% | stable | 615.099 | 3.138 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 634.708 | 0.215 |
| counters | RssAnon | 3 | 607.866 | 0.400 |
| nmt | VmRSS | 3 | 636.992 | 0.801 |
| nmt | RssAnon | 3 | 610.133 | 0.749 |
| noprof | VmRSS | 1 | 608.008 | 0.000 |
| noprof | RssAnon | 1 | 585.590 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 13.32% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 6.28% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.18% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.133 | 0.002 | 0.01% | 22.132..22.135 | stable | 22.131 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.549 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.007 | 0.002 | 28.93% | 0.005..0.009 | stable | 0.004 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.000 | 7.05% | 0.006..0.006 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.163 | 0.002 | 0.01% | 23.161..23.165 | stable | 23.160 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.01% | 4.553..4.554 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.568 | 0.004 | 0.09% | 4.564..4.572 | stable | 4.568 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.007 | 0.002 | 28.93% | 0.005..0.009 | stable | 0.004 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.000 | 7.05% | 0.006..0.006 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.133 | 0.002 | 0.01% | 22.132..22.135 | stable | 22.133 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.007 | 0.002 | 28.93% | 0.005..0.009 | stable | 0.004 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.000 | 7.05% | 0.006..0.006 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 3 | 0.720 | 0.004 | 0.49% | stable | 0.565 | 0.154 |
| thread | 3 | 21.840 | 0.002 | 0.01% | stable | 21.837 | 0.004 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.01% | stable | 7.434 | 0.006 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.324 | 0.001 | 0.46% | stable | 0.282 | 0.042 |
| total | 3 | 609.652 | 0.273 | 0.04% | stable | 609.785 | -0.133 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 613.529 | 0.207 |
| counters | RssAnon | 3 | 586.961 | 0.090 |
| nmt | VmRSS | 3 | 613.530 | 0.404 |
| nmt | RssAnon | 3 | 587.126 | 0.464 |
| noprof | VmRSS | 1 | 589.219 | 0.000 |
| noprof | RssAnon | 1 | 567.641 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.054 | 0.001 | 2.74% | 0.053..0.056 | stable | 0.053 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.078 | 0.001 | 1.18% | 0.077..0.079 | stable | 0.077 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.84% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.265 | 0.013 | 0.05% | 23.251..23.276 | stable | 23.246 |
| `native_mem_live_bytes.calltrace` | 3 | 4.260 | 0.024 | 0.56% | 4.235..4.283 | stable | 4.245 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.143 | 0.006 | 4.26% | 0.136..0.148 | stable | 0.142 |
| `native_mem_live_bytes.method_map` | 3 | 0.469 | 0.006 | 1.18% | 0.464..0.475 | stable | 0.464 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.60% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.949 | 0.033 | 0.13% | 24.923..24.986 | stable | 24.929 |
| `native_mem_max_bytes.calltrace` | 3 | 5.391 | 0.021 | 0.39% | 5.377..5.415 | stable | 5.374 |
| `native_mem_max_bytes.dictionary` | 3 | 5.097 | 0.001 | 0.03% | 5.095..5.098 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.143 | 0.006 | 4.26% | 0.136..0.148 | stable | 0.142 |
| `native_mem_max_bytes.method_map` | 3 | 0.469 | 0.006 | 1.18% | 0.464..0.475 | stable | 0.464 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.62% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.265 | 0.013 | 0.05% | 23.251..23.276 | stable | 23.246 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.001 | 0.04% | 3.623..3.626 | stable | 3.623 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.143 | 0.006 | 4.26% | 0.136..0.148 | stable | 0.142 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.469 | 0.006 | 1.18% | 0.464..0.475 | stable | 0.464 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.62% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.000 | 0.00% | stable | 8.254 | 0.459 |
| internal | 3 | 1.377 | 0.001 | 0.07% | stable | 0.784 | 0.593 |
| thread | 3 | 0.956 | 0.022 | 2.28% | stable | 0.979 | -0.023 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 29.251 | 1.348 | 4.61% | banded | 28.473 | 0.778 |
| metaspace | 3 | 21.972 | 0.036 | 0.16% | stable | 21.762 | 0.210 |
| arena_chunk | 3 | 1.255 | 0.320 | 25.51% | noisy | 0.990 | 0.265 |
| native_memory_tracking | 3 | 2.365 | 0.020 | 0.84% | stable | 2.122 | 0.243 |
| total | 3 | 646.452 | 1.348 | 0.21% | stable | 644.178 | 2.274 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 672.018 | 2.681 |
| counters | RssAnon | 3 | 645.273 | 2.530 |
| nmt | VmRSS | 3 | 676.396 | 1.768 |
| nmt | RssAnon | 3 | 649.392 | 1.703 |
| noprof | VmRSS | 1 | 660.109 | 0.000 |
| noprof | RssAnon | 1 | 637.875 | 0.000 |
