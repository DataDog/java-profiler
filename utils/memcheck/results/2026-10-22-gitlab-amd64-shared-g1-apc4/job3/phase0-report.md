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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.001 | 3.71% | 0.020..0.022 | stable | 0.021 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.041 | 0.001 | 2.93% | 0.040..0.042 | stable | 0.042 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 5.13% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.703 | 0.017 | 0.07% | 24.685..24.718 | stable | 24.716 |
| `native_mem_live_bytes.calltrace` | 3 | 3.720 | 0.009 | 0.24% | 3.709..3.725 | stable | 3.723 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.801 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.095 | 0.004 | 3.93% | 0.091..0.099 | stable | 0.099 |
| `native_mem_live_bytes.method_map` | 3 | 0.245 | 0.007 | 2.93% | 0.238..0.252 | stable | 0.252 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 6.58% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.860 | 0.020 | 0.08% | 25.840..25.880 | stable | 25.876 |
| `native_mem_max_bytes.calltrace` | 3 | 4.875 | 0.011 | 0.24% | 4.862..4.885 | stable | 4.881 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.801 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.095 | 0.004 | 3.93% | 0.091..0.099 | stable | 0.099 |
| `native_mem_max_bytes.method_map` | 3 | 0.245 | 0.007 | 2.93% | 0.238..0.252 | stable | 0.252 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.53% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.703 | 0.017 | 0.07% | 24.685..24.718 | stable | 24.716 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.001 | 0.02% | 3.566..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.049 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.095 | 0.004 | 3.93% | 0.091..0.099 | stable | 0.099 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.245 | 0.007 | 2.93% | 0.238..0.252 | stable | 0.252 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.53% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.001 | 0.01% | stable | 4.528 | 0.294 |
| internal | 3 | 0.949 | 0.005 | 0.54% | stable | 0.587 | 0.362 |
| thread | 3 | 0.932 | 0.021 | 2.30% | stable | 0.919 | 0.013 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.513 | 0.140 | 0.76% | stable | 17.046 | 1.467 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.344 | 0.432 | 125.52% | noisy | 0.126 | 0.218 |
| native_memory_tracking | 3 | 1.422 | 0.004 | 0.25% | stable | 1.220 | 0.202 |
| total | 3 | 617.873 | 0.312 | 0.05% | stable | 615.092 | 2.781 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 633.286 | 0.464 |
| counters | RssAnon | 3 | 606.688 | 0.552 |
| nmt | VmRSS | 3 | 635.647 | 0.656 |
| nmt | RssAnon | 3 | 608.897 | 0.704 |
| noprof | VmRSS | 1 | 611.324 | 0.000 |
| noprof | RssAnon | 1 | 588.777 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.108 | 0.003 | 2.75% | 0.106..0.111 | stable | 0.103 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.154 | 0.003 | 1.88% | 0.152..0.157 | stable | 0.145 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 4.65% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.313 | 0.028 | 0.11% | 26.285..26.342 | stable | 26.225 |
| `native_mem_live_bytes.calltrace` | 3 | 4.412 | 0.010 | 0.24% | 4.402..4.423 | stable | 4.389 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.335 | 0.009 | 2.57% | 0.328..0.344 | stable | 0.321 |
| `native_mem_live_bytes.method_map` | 3 | 0.922 | 0.017 | 1.86% | 0.911..0.942 | stable | 0.869 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 6.98% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.175 | 0.068 | 0.24% | 28.133..28.253 | stable | 28.051 |
| `native_mem_max_bytes.calltrace` | 3 | 6.266 | 0.042 | 0.67% | 6.242..6.315 | stable | 6.208 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.335 | 0.009 | 2.57% | 0.328..0.344 | stable | 0.321 |
| `native_mem_max_bytes.method_map` | 3 | 0.922 | 0.017 | 1.86% | 0.911..0.942 | stable | 0.869 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 5.19% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.313 | 0.028 | 0.11% | 26.285..26.342 | stable | 26.225 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.724 | 0.003 | 0.08% | 3.722..3.727 | stable | 3.720 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.335 | 0.009 | 2.57% | 0.328..0.344 | stable | 0.321 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.922 | 0.017 | 1.86% | 0.911..0.942 | stable | 0.869 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.88% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.401 | 0.001 | 0.00% | stable | 65.461 | 2.940 |
| internal | 3 | 6.721 | 0.019 | 0.28% | stable | 3.528 | 3.193 |
| thread | 3 | 0.937 | 0.002 | 0.24% | stable | 0.935 | 0.002 |
| symbol | 3 | 5.877 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 58.761 | 1.124 | 1.91% | banded | 52.425 | 6.337 |
| metaspace | 3 | 116.591 | 0.710 | 0.61% | stable | 115.275 | 1.315 |
| arena_chunk | 3 | 0.542 | 0.252 | 46.43% | noisy | 0.797 | -0.255 |
| native_memory_tracking | 3 | 12.043 | 0.039 | 0.32% | stable | 9.913 | 2.130 |
| total | 3 | 856.631 | 1.413 | 0.16% | stable | 840.736 | 15.895 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 878.661 | 2.146 |
| counters | RssAnon | 3 | 851.706 | 2.217 |
| nmt | VmRSS | 3 | 891.793 | 2.379 |
| nmt | RssAnon | 3 | 865.026 | 2.472 |
| noprof | VmRSS | 1 | 857.227 | 0.000 |
| noprof | RssAnon | 1 | 834.617 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 1.02% | 0.087..0.089 | stable | 0.087 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.000 | 0.65% | 0.073..0.074 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.53% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.157 | 0.048 | 0.18% | 26.112..26.207 | stable | 26.199 |
| `native_mem_live_bytes.calltrace` | 3 | 4.439 | 0.043 | 0.98% | 4.399..4.486 | stable | 4.476 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.135 | 0.003 | 2.33% | 0.133..0.139 | stable | 0.140 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.439 | 0.003 | 0.65% | 0.436..0.442 | stable | 0.439 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.99% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.665 | 0.013 | 0.05% | 27.651..27.676 | stable | 27.667 |
| `native_mem_max_bytes.calltrace` | 3 | 5.936 | 0.009 | 0.15% | 5.927..5.945 | stable | 5.934 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.01% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.135 | 0.003 | 2.33% | 0.133..0.139 | stable | 0.140 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.439 | 0.003 | 0.65% | 0.436..0.442 | stable | 0.439 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 4.15% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.157 | 0.048 | 0.18% | 26.112..26.207 | stable | 26.199 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.02% | 3.693..3.695 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.135 | 0.003 | 2.33% | 0.133..0.139 | stable | 0.140 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.439 | 0.003 | 0.65% | 0.436..0.442 | stable | 0.439 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 4.15% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.824 | 0.001 | 0.01% | stable | 4.528 | 0.295 |
| internal | 3 | 0.992 | 0.004 | 0.37% | stable | 0.587 | 0.405 |
| thread | 3 | 0.936 | 0.025 | 2.66% | stable | 0.919 | 0.017 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.534 | 0.102 | 0.55% | stable | 16.982 | 1.551 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.344 | 0.405 | 117.74% | noisy | 0.127 | 0.217 |
| native_memory_tracking | 3 | 1.430 | 0.006 | 0.40% | stable | 1.222 | 0.209 |
| total | 3 | 617.945 | 0.318 | 0.05% | stable | 615.037 | 2.908 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 635.862 | 0.178 |
| counters | RssAnon | 3 | 609.091 | 0.280 |
| nmt | VmRSS | 3 | 637.346 | 0.384 |
| nmt | RssAnon | 3 | 610.500 | 0.328 |
| noprof | VmRSS | 1 | 604.953 | 0.000 |
| noprof | RssAnon | 1 | 582.680 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 8.03% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 19.57% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.00% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.133 | 0.002 | 0.01% | 22.131..22.135 | stable | 22.136 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.549 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.006 | 0.001 | 9.31% | 0.005..0.007 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.001 | 19.41% | 0.006..0.008 | stable | 0.007 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.166 | 0.008 | 0.04% | 23.158..23.174 | stable | 23.168 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.000 | 0.01% | 4.554..4.554 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.571 | 0.007 | 0.15% | 4.564..4.578 | stable | 4.572 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.006 | 0.001 | 9.31% | 0.005..0.007 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.001 | 19.41% | 0.006..0.008 | stable | 0.007 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.133 | 0.002 | 0.01% | 22.131..22.135 | stable | 22.136 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.006 | 0.001 | 9.31% | 0.005..0.007 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.001 | 19.41% | 0.006..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 3 | 0.724 | 0.003 | 0.36% | stable | 0.565 | 0.158 |
| thread | 3 | 21.843 | 0.002 | 0.01% | stable | 21.837 | 0.006 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.438 | 0.002 | 0.03% | stable | 7.433 | 0.006 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.329 | 0.001 | 0.45% | stable | 0.283 | 0.046 |
| total | 3 | 610.626 | 0.387 | 0.06% | stable | 610.043 | 0.583 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 613.296 | 0.480 |
| counters | RssAnon | 3 | 586.930 | 0.464 |
| nmt | VmRSS | 3 | 613.694 | 0.325 |
| nmt | RssAnon | 3 | 587.421 | 0.270 |
| noprof | VmRSS | 1 | 589.277 | 0.000 |
| noprof | RssAnon | 1 | 567.934 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.055 | 0.001 | 1.42% | 0.054..0.056 | stable | 0.056 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.080 | 0.001 | 1.77% | 0.079..0.082 | stable | 0.080 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.84% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.312 | 0.017 | 0.07% | 23.294..23.326 | stable | 23.304 |
| `native_mem_live_bytes.calltrace` | 3 | 4.280 | 0.005 | 0.12% | 4.276..4.286 | stable | 4.283 |
| `native_mem_live_bytes.dictionary` | 3 | 4.559 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.87% | 0.147..0.156 | stable | 0.145 |
| `native_mem_live_bytes.method_map` | 3 | 0.482 | 0.009 | 1.77% | 0.474..0.491 | stable | 0.482 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.991 | 0.023 | 0.09% | 24.967..25.013 | stable | 24.987 |
| `native_mem_max_bytes.calltrace` | 3 | 5.407 | 0.011 | 0.21% | 5.396..5.418 | stable | 5.414 |
| `native_mem_max_bytes.dictionary` | 3 | 5.101 | 0.006 | 0.12% | 5.097..5.108 | stable | 5.096 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.87% | 0.147..0.156 | stable | 0.145 |
| `native_mem_max_bytes.method_map` | 3 | 0.482 | 0.009 | 1.77% | 0.474..0.491 | stable | 0.482 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 2.67% | 0.002..0.003 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.312 | 0.017 | 0.07% | 23.294..23.326 | stable | 23.304 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.625 | 0.001 | 0.02% | 3.624..3.626 | stable | 3.626 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.557 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.151 | 0.004 | 2.87% | 0.147..0.156 | stable | 0.145 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.482 | 0.009 | 1.77% | 0.474..0.491 | stable | 0.482 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 2.67% | 0.002..0.003 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.000 | 0.00% | stable | 8.254 | 0.459 |
| internal | 3 | 1.382 | 0.002 | 0.18% | stable | 0.780 | 0.602 |
| thread | 3 | 0.965 | 0.000 | 0.00% | stable | 0.972 | -0.007 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 31.551 | 2.276 | 7.21% | noisy | 25.344 | 6.207 |
| metaspace | 3 | 21.993 | 0.036 | 0.16% | stable | 21.762 | 0.231 |
| arena_chunk | 3 | 1.246 | 0.224 | 17.94% | noisy | 1.468 | -0.221 |
| native_memory_tracking | 3 | 2.406 | 0.040 | 1.67% | stable | 2.056 | 0.350 |
| total | 3 | 648.845 | 2.335 | 0.36% | stable | 641.013 | 7.832 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 673.007 | 5.090 |
| counters | RssAnon | 3 | 646.099 | 5.064 |
| nmt | VmRSS | 3 | 679.785 | 2.847 |
| nmt | RssAnon | 3 | 652.763 | 2.727 |
| noprof | VmRSS | 1 | 643.574 | 0.000 |
| noprof | RssAnon | 1 | 621.094 | 0.000 |
