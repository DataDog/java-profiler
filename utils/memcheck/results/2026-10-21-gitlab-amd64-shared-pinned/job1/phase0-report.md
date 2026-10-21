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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.020 | 0.001 | 2.76% | 0.020..0.021 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.040 | 0.001 | 2.52% | 0.039..0.041 | stable | 0.041 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.03% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.695 | 0.015 | 0.06% | 24.678..24.708 | stable | 24.705 |
| `native_mem_live_bytes.calltrace` | 3 | 3.718 | 0.007 | 0.19% | 3.713..3.726 | stable | 3.720 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.095 | 0.005 | 5.19% | 0.089..0.099 | stable | 0.095 |
| `native_mem_live_bytes.method_map` | 3 | 0.240 | 0.006 | 2.52% | 0.233..0.244 | stable | 0.246 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.845 | 0.019 | 0.07% | 25.823..25.857 | stable | 25.859 |
| `native_mem_max_bytes.calltrace` | 3 | 4.867 | 0.009 | 0.18% | 4.858..4.874 | stable | 4.875 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.095 | 0.005 | 5.19% | 0.089..0.099 | stable | 0.095 |
| `native_mem_max_bytes.method_map` | 3 | 0.240 | 0.006 | 2.52% | 0.233..0.244 | stable | 0.246 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_observed_total_bytes` | 3 | 24.695 | 0.015 | 0.06% | 24.678..24.708 | stable | 24.705 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.566 | 0.001 | 0.02% | 3.565..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.095 | 0.005 | 5.19% | 0.089..0.099 | stable | 0.095 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.240 | 0.006 | 2.52% | 0.233..0.244 | stable | 0.246 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.00% | 0.001..0.001 | stable | 0.001 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.818 | 0.001 | 0.02% | stable | 4.525 | 0.293 |
| internal | 3 | 0.862 | 0.005 | 0.58% | stable | 0.587 | 0.275 |
| thread | 3 | 0.802 | 0.000 | 0.00% | stable | 0.923 | -0.121 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.493 | 0.103 | 0.59% | stable | 16.777 | 0.716 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.242 | 0.182 | 75.51% | noisy | 0.001 | 0.241 |
| native_memory_tracking | 3 | 1.140 | 0.003 | 0.30% | stable | 1.215 | -0.075 |
| total | 3 | 565.899 | 0.123 | 0.02% | stable | 614.696 | -48.797 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 619.612 | 1.444 |
| counters | RssAnon | 3 | 594.100 | 1.575 |
| nmt | VmRSS | 3 | 619.755 | 0.147 |
| nmt | RssAnon | 3 | 594.333 | 0.154 |
| noprof | VmRSS | 1 | 605.312 | 0.000 |
| noprof | RssAnon | 1 | 582.938 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.112 | 0.006 | 5.36% | 0.109..0.119 | stable | 0.118 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.159 | 0.006 | 4.03% | 0.155..0.167 | stable | 0.164 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 13.86% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.380 | 0.105 | 0.40% | 26.309..26.500 | stable | 26.478 |
| `native_mem_live_bytes.calltrace` | 3 | 4.430 | 0.045 | 1.02% | 4.399..4.482 | stable | 4.486 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.352 | 0.021 | 6.05% | 0.337..0.376 | stable | 0.362 |
| `native_mem_live_bytes.method_map` | 3 | 0.955 | 0.039 | 4.03% | 0.930..1.000 | stable | 0.987 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.80% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 28.321 | 0.190 | 0.67% | 28.203..28.540 | stable | 28.495 |
| `native_mem_max_bytes.calltrace` | 3 | 6.363 | 0.131 | 2.05% | 6.284..6.513 | banded | 6.494 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.352 | 0.021 | 6.05% | 0.337..0.376 | stable | 0.362 |
| `native_mem_max_bytes.method_map` | 3 | 0.955 | 0.039 | 4.03% | 0.930..1.000 | stable | 0.987 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 13.64% | 0.001..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.380 | 0.105 | 0.40% | 26.309..26.500 | stable | 26.478 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.729 | 0.006 | 0.16% | 3.725..3.736 | stable | 3.735 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.352 | 0.021 | 6.05% | 0.337..0.376 | stable | 0.362 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.955 | 0.039 | 4.03% | 0.930..1.000 | stable | 0.987 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 13.64% | 0.001..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.459 | 2.940 |
| internal | 3 | 6.741 | 0.038 | 0.56% | stable | 3.447 | 3.294 |
| thread | 3 | 0.863 | 0.050 | 5.75% | stable | 0.805 | 0.058 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 57.303 | 0.388 | 0.68% | stable | 52.870 | 4.433 |
| metaspace | 3 | 116.164 | 2.182 | 1.88% | banded | 114.292 | 1.872 |
| arena_chunk | 3 | 0.532 | 0.356 | 66.98% | noisy | 0.672 | -0.140 |
| native_memory_tracking | 3 | 11.775 | 0.469 | 3.98% | banded | 9.180 | 2.596 |
| total | 3 | 834.229 | 29.288 | 3.51% | banded | 787.405 | 46.823 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 866.599 | 10.393 |
| counters | RssAnon | 3 | 840.146 | 10.007 |
| nmt | VmRSS | 3 | 879.750 | 12.494 |
| nmt | RssAnon | 3 | 853.107 | 11.859 |
| noprof | VmRSS | 1 | 825.121 | 0.000 |
| noprof | RssAnon | 1 | 803.918 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.090 | 0.001 | 1.42% | 0.089..0.091 | stable | 0.090 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.074 | 0.002 | 3.04% | 0.072..0.076 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 13.32% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.317 | 0.065 | 0.25% | 26.249..26.378 | stable | 26.335 |
| `native_mem_live_bytes.calltrace` | 3 | 4.597 | 0.064 | 1.39% | 4.523..4.642 | banded | 4.611 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.145 | 0.005 | 3.71% | 0.141..0.151 | stable | 0.143 |
| `native_mem_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.494 |
| `native_mem_live_bytes.method_map` | 3 | 0.443 | 0.013 | 3.04% | 0.433..0.458 | stable | 0.442 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.001 | 0.000 | 18.59% | 0.001..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.717 | 0.046 | 0.16% | 27.689..27.770 | stable | 27.716 |
| `native_mem_max_bytes.calltrace` | 3 | 5.988 | 0.034 | 0.57% | 5.958..6.025 | stable | 5.983 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.145 | 0.005 | 3.71% | 0.141..0.151 | stable | 0.143 |
| `native_mem_max_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.494 |
| `native_mem_max_bytes.method_map` | 3 | 0.443 | 0.013 | 3.04% | 0.433..0.458 | stable | 0.442 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 20.11% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.317 | 0.065 | 0.25% | 26.249..26.378 | stable | 26.335 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.696 | 0.001 | 0.04% | 3.695..3.697 | stable | 3.696 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.145 | 0.005 | 3.71% | 0.141..0.151 | stable | 0.143 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.489 | 0.010 | 1.99% | 0.483..0.500 | stable | 0.494 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.443 | 0.013 | 3.04% | 0.433..0.458 | stable | 0.442 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 20.11% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.821 | 0.004 | 0.08% | stable | 4.527 | 0.293 |
| internal | 3 | 0.967 | 0.043 | 4.43% | stable | 0.585 | 0.382 |
| thread | 3 | 0.873 | 0.059 | 6.72% | stable | 0.896 | -0.023 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 17.665 | 0.216 | 1.22% | banded | 16.563 | 1.102 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.368 | 0.149 | 40.60% | noisy | 0.391 | -0.023 |
| native_memory_tracking | 3 | 1.300 | 0.137 | 10.51% | noisy | 1.132 | 0.168 |
| total | 3 | 598.751 | 28.396 | 4.74% | banded | 612.629 | -13.878 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 623.930 | 7.037 |
| counters | RssAnon | 3 | 597.768 | 6.281 |
| nmt | VmRSS | 3 | 629.499 | 7.261 |
| nmt | RssAnon | 3 | 603.061 | 6.465 |
| noprof | VmRSS | 1 | 602.941 | 0.000 |
| noprof | RssAnon | 1 | 580.664 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 25.00% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 37.18% | 0.001..0.002 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.00% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.138 | 0.008 | 0.04% | 22.130..22.146 | stable | 22.130 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.547..3.548 | stable | 3.547 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.011 | 0.005 | 43.36% | 0.006..0.016 | stable | 0.004 |
| `native_mem_live_bytes.method_map` | 3 | 0.008 | 0.003 | 37.73% | 0.005..0.010 | stable | 0.005 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.186 | 0.029 | 0.12% | 23.155..23.212 | stable | 23.161 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.002 | 0.03% | 4.552..4.555 | stable | 4.553 |
| `native_mem_max_bytes.dictionary` | 3 | 4.586 | 0.020 | 0.43% | 4.564..4.603 | stable | 4.570 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.011 | 0.005 | 43.36% | 0.006..0.016 | stable | 0.004 |
| `native_mem_max_bytes.method_map` | 3 | 0.008 | 0.003 | 37.73% | 0.005..0.010 | stable | 0.005 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.14% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.138 | 0.008 | 0.04% | 22.130..22.146 | stable | 22.132 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.011 | 0.005 | 43.36% | 0.006..0.016 | stable | 0.004 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.008 | 0.003 | 37.73% | 0.005..0.010 | stable | 0.005 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.14% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.112 |
| internal | 3 | 0.719 | 0.005 | 0.64% | stable | 0.563 | 0.156 |
| thread | 3 | 21.832 | 0.008 | 0.04% | stable | 21.822 | 0.010 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.01% | stable | 7.433 | 0.006 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.049 | 0.072 | 148.79% | noisy | 0.007 | 0.042 |
| native_memory_tracking | 3 | 0.323 | 0.000 | 0.00% | stable | 0.277 | 0.046 |
| total | 3 | 608.299 | 1.159 | 0.19% | stable | 607.040 | 1.258 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 613.090 | 0.154 |
| counters | RssAnon | 3 | 586.621 | 0.068 |
| nmt | VmRSS | 3 | 613.306 | 0.213 |
| nmt | RssAnon | 3 | 586.862 | 0.053 |
| noprof | VmRSS | 1 | 588.555 | 0.000 |
| noprof | RssAnon | 1 | 567.219 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.055 | 0.002 | 4.57% | 0.053..0.057 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.078 | 0.003 | 3.67% | 0.075..0.081 | stable | 0.080 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 6.96% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.254 | 0.040 | 0.17% | 23.209..23.288 | stable | 23.274 |
| `native_mem_live_bytes.calltrace` | 3 | 4.238 | 0.013 | 0.32% | 4.223..4.247 | stable | 4.242 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.152 | 0.010 | 6.84% | 0.141..0.162 | stable | 0.153 |
| `native_mem_live_bytes.method_map` | 3 | 0.471 | 0.017 | 3.67% | 0.452..0.486 | stable | 0.480 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 10.28% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.982 | 0.078 | 0.31% | 24.915..25.067 | stable | 25.008 |
| `native_mem_max_bytes.calltrace` | 3 | 5.410 | 0.046 | 0.86% | 5.375..5.462 | stable | 5.423 |
| `native_mem_max_bytes.dictionary` | 3 | 5.101 | 0.007 | 0.13% | 5.097..5.108 | stable | 5.103 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.152 | 0.010 | 6.84% | 0.141..0.162 | stable | 0.153 |
| `native_mem_max_bytes.method_map` | 3 | 0.471 | 0.017 | 3.67% | 0.452..0.486 | stable | 0.480 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.87% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.254 | 0.040 | 0.17% | 23.209..23.288 | stable | 23.274 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.625 | 0.002 | 0.07% | 3.623..3.628 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.152 | 0.010 | 6.84% | 0.141..0.162 | stable | 0.153 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.471 | 0.017 | 3.67% | 0.452..0.486 | stable | 0.480 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 14.87% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.001 | 0.01% | stable | 8.251 | 0.462 |
| internal | 3 | 1.384 | 0.012 | 0.88% | stable | 0.698 | 0.686 |
| thread | 3 | 0.906 | 0.025 | 2.80% | stable | 0.797 | 0.109 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 27.923 | 2.554 | 9.15% | noisy | 21.494 | 6.429 |
| metaspace | 3 | 21.978 | 0.046 | 0.21% | stable | 21.753 | 0.225 |
| arena_chunk | 3 | 0.969 | 0.323 | 33.31% | noisy | 0.417 | 0.552 |
| native_memory_tracking | 3 | 2.359 | 0.071 | 3.01% | banded | 1.673 | 0.687 |
| total | 3 | 642.041 | 1.652 | 0.26% | stable | 584.953 | 57.088 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 666.332 | 7.729 |
| counters | RssAnon | 3 | 639.302 | 7.621 |
| nmt | VmRSS | 3 | 666.305 | 2.584 |
| nmt | RssAnon | 3 | 639.487 | 2.661 |
| noprof | VmRSS | 1 | 617.883 | 0.000 |
| noprof | RssAnon | 1 | 596.680 | 0.000 |
