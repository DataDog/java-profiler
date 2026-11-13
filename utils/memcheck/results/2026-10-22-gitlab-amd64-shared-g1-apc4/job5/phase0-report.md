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
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 1.74% | 0.021..0.022 | stable | 0.022 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.042 | 0.000 | 1.09% | 0.042..0.043 | stable | 0.043 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.63% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.716 | 0.004 | 0.01% | 24.712..24.720 | stable | 24.711 |
| `native_mem_live_bytes.calltrace` | 3 | 3.717 | 0.005 | 0.13% | 3.712..3.721 | stable | 3.713 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.103 | 0.001 | 0.79% | 0.102..0.103 | stable | 0.099 |
| `native_mem_live_bytes.method_map` | 3 | 0.253 | 0.003 | 1.09% | 0.250..0.255 | stable | 0.256 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.01% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.882 | 0.009 | 0.04% | 25.872..25.889 | stable | 25.886 |
| `native_mem_max_bytes.calltrace` | 3 | 4.882 | 0.007 | 0.14% | 4.873..4.886 | stable | 4.886 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.103 | 0.001 | 0.79% | 0.102..0.103 | stable | 0.099 |
| `native_mem_max_bytes.method_map` | 3 | 0.253 | 0.003 | 1.09% | 0.250..0.255 | stable | 0.256 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.82% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.716 | 0.004 | 0.01% | 24.712..24.720 | stable | 24.711 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.567 | 0.000 | 0.01% | 3.567..3.567 | stable | 3.567 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.103 | 0.001 | 0.79% | 0.102..0.103 | stable | 0.099 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.253 | 0.003 | 1.09% | 0.250..0.255 | stable | 0.256 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.82% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.822 | 0.001 | 0.02% | stable | 4.527 | 0.295 |
| internal | 3 | 0.949 | 0.002 | 0.18% | stable | 0.587 | 0.362 |
| thread | 3 | 0.934 | 0.024 | 2.54% | stable | 0.919 | 0.015 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.581 | 0.038 | 0.20% | stable | 16.914 | 1.667 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.344 | 0.432 | 125.52% | noisy | 0.001 | 0.343 |
| native_memory_tracking | 3 | 1.423 | 0.000 | 0.00% | stable | 1.218 | 0.205 |
| total | 3 | 617.938 | 0.439 | 0.07% | stable | 614.835 | 3.104 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 634.647 | 0.439 |
| counters | RssAnon | 3 | 607.956 | 0.317 |
| nmt | VmRSS | 3 | 637.299 | 0.689 |
| nmt | RssAnon | 3 | 610.590 | 0.667 |
| noprof | VmRSS | 1 | 603.309 | 0.000 |
| noprof | RssAnon | 1 | 581.172 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.109 | 0.003 | 3.19% | 0.105..0.111 | stable | 0.107 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.151 | 0.003 | 2.06% | 0.148..0.154 | stable | 0.150 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.77% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.287 | 0.037 | 0.14% | 26.244..26.308 | stable | 26.278 |
| `native_mem_live_bytes.calltrace` | 3 | 4.402 | 0.014 | 0.31% | 4.391..4.417 | stable | 4.401 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.334 | 0.010 | 3.06% | 0.323..0.343 | stable | 0.330 |
| `native_mem_live_bytes.method_map` | 3 | 0.907 | 0.019 | 2.05% | 0.886..0.922 | stable | 0.901 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.49% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.174 | 0.076 | 0.27% | 28.087..28.228 | stable | 28.148 |
| `native_mem_max_bytes.calltrace` | 3 | 6.282 | 0.048 | 0.77% | 6.226..6.311 | stable | 6.264 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.334 | 0.010 | 3.06% | 0.323..0.343 | stable | 0.330 |
| `native_mem_max_bytes.method_map` | 3 | 0.907 | 0.019 | 2.05% | 0.886..0.922 | stable | 0.901 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.49% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.287 | 0.037 | 0.14% | 26.244..26.308 | stable | 26.278 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.725 | 0.003 | 0.09% | 3.721..3.727 | stable | 3.724 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.334 | 0.010 | 3.06% | 0.323..0.343 | stable | 0.330 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.907 | 0.019 | 2.05% | 0.886..0.922 | stable | 0.901 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.400 | 0.000 | 0.00% | stable | 65.462 | 2.938 |
| internal | 3 | 6.730 | 0.009 | 0.13% | stable | 3.532 | 3.198 |
| thread | 3 | 0.933 | 0.002 | 0.24% | stable | 0.931 | 0.002 |
| symbol | 3 | 5.878 | 0.000 | 0.00% | stable | 5.856 | 0.021 |
| code | 3 | 58.744 | 1.051 | 1.79% | banded | 53.305 | 5.439 |
| metaspace | 3 | 116.111 | 0.634 | 0.55% | stable | 115.893 | 0.218 |
| arena_chunk | 3 | 0.702 | 0.001 | 0.08% | stable | 0.702 | 0.000 |
| native_memory_tracking | 3 | 12.028 | 0.039 | 0.32% | stable | 9.969 | 2.060 |
| total | 3 | 856.140 | 1.582 | 0.18% | stable | 842.226 | 13.914 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 880.404 | 4.019 |
| counters | RssAnon | 3 | 853.486 | 4.044 |
| nmt | VmRSS | 3 | 891.139 | 4.312 |
| nmt | RssAnon | 3 | 864.186 | 4.370 |
| noprof | VmRSS | 1 | 847.230 | 0.000 |
| noprof | RssAnon | 1 | 824.613 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 1.21% | 0.087..0.089 | stable | 0.087 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.000 | 0.66% | 0.072..0.073 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.55% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.164 | 0.025 | 0.10% | 26.146..26.193 | stable | 26.159 |
| `native_mem_live_bytes.calltrace` | 3 | 4.450 | 0.024 | 0.53% | 4.427..4.475 | stable | 4.437 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.78% | 0.128..0.138 | stable | 0.138 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.437 | 0.003 | 0.66% | 0.434..0.440 | stable | 0.438 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 2.01% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.663 | 0.009 | 0.03% | 27.658..27.674 | stable | 27.659 |
| `native_mem_max_bytes.calltrace` | 3 | 5.939 | 0.016 | 0.28% | 5.929..5.958 | stable | 5.928 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.78% | 0.128..0.138 | stable | 0.138 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.437 | 0.003 | 0.66% | 0.434..0.440 | stable | 0.438 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 0.42% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.164 | 0.025 | 0.10% | 26.146..26.193 | stable | 26.159 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.695 | 0.001 | 0.03% | 3.694..3.696 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.78% | 0.128..0.138 | stable | 0.138 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.437 | 0.003 | 0.66% | 0.434..0.440 | stable | 0.438 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 0.42% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.79% | 0.055..0.056 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.823 | 0.000 | 0.00% | stable | 4.528 | 0.295 |
| internal | 3 | 0.991 | 0.004 | 0.40% | stable | 0.587 | 0.404 |
| thread | 3 | 0.924 | 0.000 | 0.00% | stable | 0.919 | 0.005 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 18.577 | 0.078 | 0.42% | stable | 16.979 | 1.599 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.095 | 0.000 | 0.00% | stable | 0.001 | 0.094 |
| native_memory_tracking | 3 | 1.431 | 0.001 | 0.04% | stable | 1.221 | 0.211 |
| total | 3 | 617.726 | 0.081 | 0.01% | stable | 614.902 | 2.823 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 636.000 | 0.545 |
| counters | RssAnon | 3 | 609.117 | 0.264 |
| nmt | VmRSS | 3 | 638.546 | 0.544 |
| nmt | RssAnon | 3 | 611.665 | 0.622 |
| noprof | VmRSS | 1 | 603.715 | 0.000 |
| noprof | RssAnon | 1 | 581.430 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 16.50% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 6.80% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.18% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.129 | 0.003 | 0.01% | 22.125..22.131 | stable | 22.134 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.004 | 0.002 | 61.15% | 0.001..0.006 | stable | 0.007 |
| `native_mem_live_bytes.method_map` | 3 | 0.005 | 0.000 | 7.19% | 0.005..0.005 | stable | 0.007 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.28% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.154 | 0.005 | 0.02% | 23.149..23.160 | stable | 23.168 |
| `native_mem_max_bytes.calltrace` | 3 | 4.553 | 0.001 | 0.01% | 4.553..4.554 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.565 | 0.003 | 0.07% | 4.562..4.568 | stable | 4.573 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.004 | 0.002 | 61.15% | 0.001..0.006 | stable | 0.007 |
| `native_mem_max_bytes.method_map` | 3 | 0.005 | 0.000 | 7.19% | 0.005..0.005 | stable | 0.007 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.130 | 0.001 | 0.00% | 22.130..22.131 | stable | 22.134 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.004 | 0.002 | 61.15% | 0.001..0.006 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.005 | 0.000 | 7.19% | 0.005..0.005 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 3 | 0.723 | 0.003 | 0.36% | stable | 0.564 | 0.158 |
| thread | 3 | 21.844 | 0.002 | 0.01% | stable | 21.833 | 0.011 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.439 | 0.001 | 0.01% | stable | 7.434 | 0.005 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 3 | 0.329 | 0.003 | 1.04% | stable | 0.282 | 0.047 |
| total | 3 | 610.518 | 0.688 | 0.11% | stable | 609.820 | 0.698 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 614.342 | 0.282 |
| counters | RssAnon | 3 | 587.927 | 0.292 |
| nmt | VmRSS | 3 | 614.867 | 0.503 |
| nmt | RssAnon | 3 | 588.419 | 0.390 |
| noprof | VmRSS | 1 | 588.898 | 0.000 |
| noprof | RssAnon | 1 | 567.672 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.054 | 0.002 | 3.34% | 0.053..0.056 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.080 | 0.002 | 3.11% | 0.078..0.082 | stable | 0.081 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 6.09% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.283 | 0.060 | 0.26% | 23.241..23.352 | stable | 23.294 |
| `native_mem_live_bytes.calltrace` | 3 | 4.263 | 0.039 | 0.91% | 4.241..4.308 | stable | 4.258 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.149 | 0.008 | 5.47% | 0.141..0.157 | stable | 0.150 |
| `native_mem_live_bytes.method_map` | 3 | 0.477 | 0.015 | 3.11% | 0.466..0.494 | stable | 0.486 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 4.76% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 24.967 | 0.054 | 0.22% | 24.918..25.025 | stable | 24.991 |
| `native_mem_max_bytes.calltrace` | 3 | 5.393 | 0.030 | 0.55% | 5.367..5.425 | stable | 5.405 |
| `native_mem_max_bytes.dictionary` | 3 | 5.097 | 0.002 | 0.05% | 5.095..5.099 | stable | 5.101 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.149 | 0.008 | 5.47% | 0.141..0.157 | stable | 0.150 |
| `native_mem_max_bytes.method_map` | 3 | 0.477 | 0.015 | 3.11% | 0.466..0.494 | stable | 0.486 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.60% | 0.002..0.002 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.283 | 0.060 | 0.26% | 23.241..23.352 | stable | 23.294 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.002 | 0.05% | 3.623..3.626 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.149 | 0.008 | 5.47% | 0.141..0.157 | stable | 0.150 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.477 | 0.015 | 3.11% | 0.466..0.494 | stable | 0.486 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.60% | 0.002..0.002 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.713 | 0.001 | 0.01% | stable | 8.254 | 0.459 |
| internal | 3 | 1.387 | 0.002 | 0.16% | stable | 0.779 | 0.608 |
| thread | 3 | 0.973 | 0.000 | 0.00% | stable | 0.979 | -0.007 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 29.957 | 1.993 | 6.65% | noisy | 23.775 | 6.181 |
| metaspace | 3 | 21.999 | 0.041 | 0.19% | stable | 21.762 | 0.237 |
| arena_chunk | 3 | 1.354 | 0.018 | 1.31% | stable | 1.405 | -0.052 |
| native_memory_tracking | 3 | 2.376 | 0.035 | 1.49% | stable | 2.024 | 0.352 |
| total | 3 | 647.175 | 2.124 | 0.33% | stable | 639.333 | 7.842 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 677.581 | 2.390 |
| counters | RssAnon | 3 | 650.816 | 2.262 |
| nmt | VmRSS | 3 | 675.887 | 2.983 |
| nmt | RssAnon | 3 | 649.043 | 2.807 |
| noprof | VmRSS | 1 | 654.527 | 0.000 |
| noprof | RssAnon | 1 | 632.035 | 0.000 |
