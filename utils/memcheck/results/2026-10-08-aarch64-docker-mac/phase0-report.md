# Phase 0: memcheck noise

- profiler-commit: `a60c7b1cf727db96c376063c2c0e7c525c39a585`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `4`
- runs: counters=50, nmt=50, noprof=15

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.029 | 0.000 | 1.32% | 0.028..0.029 | stable | 0.029 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.057 | 0.001 | 1.11% | 0.056..0.058 | stable | 0.057 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.920 | 0.000 | 0.00% | 0.920..0.920 | stable | 0.920 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 5.19% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 22.074 | 0.010 | 0.05% | 22.058..22.094 | stable | 22.081 |
| `native_mem_live_bytes.calltrace` | 10 | 3.719 | 0.006 | 0.15% | 3.711..3.727 | stable | 3.723 |
| `native_mem_live_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.120 | 0.004 | 3.13% | 0.115..0.126 | stable | 0.119 |
| `native_mem_live_bytes.method_map` | 10 | 0.340 | 0.004 | 1.11% | 0.336..0.347 | stable | 0.342 |
| `native_mem_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 10 | 23.346 | 0.012 | 0.05% | 23.331..23.366 | stable | 23.352 |
| `native_mem_max_bytes.calltrace` | 10 | 4.989 | 0.006 | 0.12% | 4.979..4.998 | stable | 4.994 |
| `native_mem_max_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.120 | 0.004 | 3.13% | 0.115..0.126 | stable | 0.119 |
| `native_mem_max_bytes.method_map` | 10 | 0.340 | 0.004 | 1.11% | 0.336..0.347 | stable | 0.342 |
| `native_mem_max_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.002 | 0.000 | 1.73% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 10 | 22.074 | 0.010 | 0.05% | 22.058..22.094 | stable | 22.081 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.571 | 0.000 | 0.01% | 3.570..3.571 | stable | 3.571 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.120 | 0.004 | 3.13% | 0.115..0.126 | stable | 0.119 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.340 | 0.004 | 1.11% | 0.336..0.347 | stable | 0.342 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 1.73% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 4.882 | 0.001 | 0.01% | stable | 4.524 | 0.358 |
| internal | 10 | 1.843 | 0.003 | 0.18% | stable | 1.462 | 0.381 |
| thread | 10 | 1.014 | 0.000 | 0.00% | stable | 1.013 | 0.001 |
| symbol | 10 | 1.594 | 0.000 | 0.03% | stable | 1.573 | 0.021 |
| code | 10 | 20.199 | 0.055 | 0.27% | stable | 18.499 | 1.699 |
| metaspace | 10 | 11.579 | 0.000 | 0.00% | stable | 11.328 | 0.251 |
| arena_chunk | 10 | 0.032 | 0.000 | 0.00% | stable | 0.001 | 0.031 |
| native_memory_tracking | 10 | 1.378 | 0.004 | 0.28% | stable | 1.168 | 0.209 |
| total | 10 | 619.648 | 0.076 | 0.01% | stable | 616.687 | 2.961 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 633.550 | 1.702 |
| counters | RssAnon | 10 | 608.880 | 3.352 |
| nmt | VmRSS | 10 | 635.647 | 1.234 |
| nmt | RssAnon | 10 | 611.573 | 1.234 |
| noprof | VmRSS | 3 | 608.488 | 2.747 |
| noprof | RssAnon | 3 | 588.383 | 2.754 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.048 | 0.003 | 5.68% | 0.044..0.050 | stable | 0.047 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.073 | 0.004 | 5.06% | 0.067..0.076 | stable | 0.072 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.920 | 0.000 | 0.00% | 0.920..0.920 | stable | 0.920 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 2.10% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 22.757 | 0.066 | 0.29% | 22.658..22.806 | stable | 22.731 |
| `native_mem_live_bytes.calltrace` | 10 | 4.270 | 0.038 | 0.88% | 4.214..4.296 | stable | 4.255 |
| `native_mem_live_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.152 | 0.007 | 4.84% | 0.141..0.161 | stable | 0.148 |
| `native_mem_live_bytes.method_map` | 10 | 0.438 | 0.022 | 5.05% | 0.403..0.456 | stable | 0.429 |
| `native_mem_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.003 | 0.000 | 0.83% | 0.003..0.003 | stable | 0.003 |
| `native_mem_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 10 | 23.812 | 0.067 | 0.28% | 23.709..23.865 | stable | 23.792 |
| `native_mem_max_bytes.calltrace` | 10 | 5.316 | 0.038 | 0.72% | 5.256..5.345 | stable | 5.309 |
| `native_mem_max_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.152 | 0.007 | 4.84% | 0.141..0.161 | stable | 0.148 |
| `native_mem_max_bytes.method_map` | 10 | 0.438 | 0.022 | 5.05% | 0.403..0.456 | stable | 0.429 |
| `native_mem_max_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.003 | 0.000 | 0.83% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 22.757 | 0.066 | 0.29% | 22.658..22.806 | stable | 22.731 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.614 | 0.003 | 0.08% | 3.610..3.616 | stable | 3.614 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.152 | 0.007 | 4.84% | 0.141..0.161 | stable | 0.148 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.438 | 0.022 | 5.05% | 0.403..0.456 | stable | 0.429 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 68.399 | 0.001 | 0.00% | stable | 65.459 | 2.940 |
| internal | 10 | 6.357 | 0.007 | 0.11% | stable | 3.345 | 3.013 |
| thread | 10 | 1.095 | 0.004 | 0.37% | stable | 1.098 | -0.003 |
| symbol | 10 | 5.878 | 0.000 | 0.01% | stable | 5.857 | 0.020 |
| code | 10 | 73.489 | 0.504 | 0.69% | stable | 61.344 | 12.145 |
| metaspace | 10 | 116.981 | 0.421 | 0.36% | stable | 116.958 | 0.023 |
| arena_chunk | 10 | 1.115 | 0.211 | 18.91% | noisy | 1.333 | -0.218 |
| native_memory_tracking | 10 | 11.046 | 0.032 | 0.29% | stable | 9.071 | 1.975 |
| total | 10 | 867.421 | 0.955 | 0.11% | stable | 847.825 | 19.596 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 895.070 | 5.843 |
| counters | RssAnon | 10 | 870.316 | 6.242 |
| nmt | VmRSS | 10 | 902.587 | 3.430 |
| nmt | RssAnon | 10 | 877.832 | 4.093 |
| noprof | VmRSS | 3 | 851.297 | 5.766 |
| noprof | RssAnon | 3 | 831.237 | 5.767 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.088 | 0.002 | 2.30% | 0.086..0.092 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.069 | 0.000 | 0.43% | 0.068..0.069 | stable | 0.069 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.920 | 0.000 | 0.00% | 0.920..0.920 | stable | 0.920 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 6.40% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 23.199 | 0.015 | 0.07% | 23.177..23.225 | stable | 23.197 |
| `native_mem_live_bytes.calltrace` | 10 | 4.258 | 0.015 | 0.35% | 4.238..4.290 | stable | 4.260 |
| `native_mem_live_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.132 | 0.003 | 2.39% | 0.128..0.138 | stable | 0.130 |
| `native_mem_live_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 10 | 0.414 | 0.002 | 0.43% | 0.411..0.417 | stable | 0.411 |
| `native_mem_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 10 | 24.851 | 0.027 | 0.11% | 24.821..24.890 | stable | 24.847 |
| `native_mem_max_bytes.calltrace` | 10 | 5.900 | 0.025 | 0.42% | 5.871..5.939 | stable | 5.901 |
| `native_mem_max_bytes.dictionary` | 10 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.132 | 0.003 | 2.39% | 0.128..0.138 | stable | 0.130 |
| `native_mem_max_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 10 | 0.414 | 0.002 | 0.43% | 0.411..0.417 | stable | 0.411 |
| `native_mem_max_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.003 | 0.000 | 2.40% | 0.002..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 10 | 0.056 | 0.000 | 0.00% | 0.056..0.056 | stable | 0.056 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 23.199 | 0.015 | 0.07% | 23.177..23.225 | stable | 23.197 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.691 | 0.002 | 0.06% | 3.688..3.694 | stable | 3.691 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.132 | 0.003 | 2.39% | 0.128..0.138 | stable | 0.130 |
| `native_mem_post_flush_live_bytes.liveness` | 10 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.414 | 0.002 | 0.43% | 0.411..0.417 | stable | 0.411 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.003 | 0.000 | 2.40% | 0.002..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 4.882 | 0.001 | 0.01% | stable | 4.524 | 0.358 |
| internal | 10 | 1.856 | 0.006 | 0.33% | stable | 1.462 | 0.394 |
| thread | 10 | 1.030 | 0.001 | 0.12% | stable | 1.013 | 0.017 |
| symbol | 10 | 1.595 | 0.000 | 0.03% | stable | 1.573 | 0.021 |
| code | 10 | 20.178 | 0.046 | 0.23% | stable | 18.433 | 1.746 |
| metaspace | 10 | 11.579 | 0.000 | 0.00% | stable | 11.328 | 0.251 |
| arena_chunk | 10 | 0.032 | 0.000 | 0.00% | stable | 0.001 | 0.031 |
| native_memory_tracking | 10 | 1.378 | 0.004 | 0.29% | stable | 1.167 | 0.212 |
| total | 10 | 619.664 | 0.065 | 0.01% | stable | 616.653 | 3.010 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 636.363 | 3.681 |
| counters | RssAnon | 10 | 611.618 | 4.535 |
| nmt | VmRSS | 10 | 636.834 | 1.236 |
| nmt | RssAnon | 10 | 612.677 | 1.230 |
| noprof | VmRSS | 3 | 607.013 | 4.078 |
| noprof | RssAnon | 3 | 586.909 | 4.075 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.000 | 0.000 | 14.72% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.001 | 0.000 | 25.18% | 0.000..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.920 | 0.000 | 0.00% | 0.920..0.920 | stable | 0.920 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.005 | 0.000 | 0.26% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 10 | 19.375 | 0.004 | 0.02% | 19.371..19.383 | stable | 19.380 |
| `native_mem_live_bytes.calltrace` | 10 | 3.544 | 0.000 | 0.01% | 3.544..3.545 | stable | 3.544 |
| `native_mem_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.003 | 0.003 | 102.30% | 0.001..0.008 | stable | 0.006 |
| `native_mem_live_bytes.method_map` | 10 | 0.004 | 0.001 | 25.66% | 0.002..0.006 | stable | 0.005 |
| `native_mem_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_live_bytes.thread_local` | 10 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 10 | 20.398 | 0.005 | 0.02% | 20.393..20.409 | stable | 20.407 |
| `native_mem_max_bytes.calltrace` | 10 | 4.549 | 0.001 | 0.01% | 4.549..4.550 | stable | 4.550 |
| `native_mem_max_bytes.dictionary` | 10 | 4.563 | 0.001 | 0.03% | 4.561..4.565 | stable | 4.566 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.003 | 0.003 | 102.30% | 0.001..0.008 | stable | 0.006 |
| `native_mem_max_bytes.method_map` | 10 | 0.004 | 0.001 | 25.66% | 0.002..0.006 | stable | 0.005 |
| `native_mem_max_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_max_bytes.thread_local` | 10 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 19.379 | 0.002 | 0.01% | 19.377..19.383 | stable | 19.382 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.542 | 0.000 | 0.00% | 3.542..3.542 | stable | 3.542 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.003 | 0.003 | 102.30% | 0.001..0.008 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.004 | 0.001 | 25.66% | 0.002..0.006 | stable | 0.005 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.028 | 0.000 | 0.00% | 0.028..0.028 | stable | 0.028 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 0.383 | 0.000 | 0.00% | stable | 0.271 | 0.111 |
| internal | 10 | 1.713 | 0.004 | 0.21% | stable | 1.561 | 0.153 |
| thread | 10 | 22.747 | 0.003 | 0.01% | stable | 22.193 | 0.554 |
| symbol | 10 | 1.133 | 0.000 | 0.00% | stable | 1.119 | 0.014 |
| code | 10 | 7.435 | 0.001 | 0.01% | stable | 7.428 | 0.007 |
| metaspace | 10 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 10 | 0.007 | 0.000 | 0.00% | stable | 0.007 | 0.000 |
| native_memory_tracking | 10 | 0.371 | 0.001 | 0.25% | stable | 0.329 | 0.042 |
| total | 10 | 611.027 | 0.047 | 0.01% | stable | 610.007 | 1.020 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 608.562 | 0.076 |
| counters | RssAnon | 10 | 584.595 | 0.081 |
| nmt | VmRSS | 10 | 609.091 | 0.059 |
| nmt | RssAnon | 10 | 585.130 | 0.059 |
| noprof | VmRSS | 3 | 586.557 | 0.067 |
| noprof | RssAnon | 3 | 566.992 | 0.042 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 10 | 0.049 | 0.002 | 5.05% | 0.045..0.050 | stable | 0.049 |
| `native_mem_chunk_overhead_bytes.dictionary` | 10 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 10 | 0.060 | 0.002 | 4.03% | 0.056..0.063 | stable | 0.060 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 10 | 0.920 | 0.000 | 0.00% | 0.920..0.920 | stable | 0.920 |
| `native_mem_chunk_overhead_bytes.thread_info` | 10 | 0.000 | 0.000 | 4.74% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 10 | 20.289 | 0.058 | 0.29% | 20.204..20.337 | stable | 20.287 |
| `native_mem_live_bytes.calltrace` | 10 | 4.191 | 0.039 | 0.94% | 4.132..4.224 | stable | 4.191 |
| `native_mem_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.555 |
| `native_mem_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 10 | 0.089 | 0.006 | 6.59% | 0.082..0.097 | stable | 0.085 |
| `native_mem_live_bytes.method_map` | 10 | 0.363 | 0.015 | 4.03% | 0.338..0.377 | stable | 0.361 |
| `native_mem_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 3.67% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 10 | 0.054 | 0.000 | 0.60% | 0.053..0.054 | stable | 0.054 |
| `native_mem_max_bytes` | 10 | 21.935 | 0.052 | 0.24% | 21.852..21.977 | stable | 21.931 |
| `native_mem_max_bytes.calltrace` | 10 | 5.298 | 0.032 | 0.61% | 5.247..5.322 | stable | 5.298 |
| `native_mem_max_bytes.dictionary` | 10 | 5.084 | 0.002 | 0.04% | 5.082..5.088 | stable | 5.084 |
| `native_mem_max_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 10 | 0.089 | 0.006 | 6.59% | 0.082..0.097 | stable | 0.085 |
| `native_mem_max_bytes.method_map` | 10 | 0.363 | 0.015 | 4.03% | 0.338..0.377 | stable | 0.361 |
| `native_mem_max_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_max_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 10 | 0.002 | 0.000 | 2.54% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 10 | 20.289 | 0.058 | 0.29% | 20.204..20.337 | stable | 20.287 |
| `native_mem_post_flush_live_bytes.calltrace` | 10 | 3.615 | 0.002 | 0.07% | 3.611..3.617 | stable | 3.615 |
| `native_mem_post_flush_live_bytes.dictionary` | 10 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.554 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 10 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 10 | 0.089 | 0.006 | 6.59% | 0.082..0.097 | stable | 0.085 |
| `native_mem_post_flush_live_bytes.method_map` | 10 | 0.363 | 0.015 | 4.03% | 0.338..0.377 | stable | 0.361 |
| `native_mem_post_flush_live_bytes.native_symbols` | 10 | 9.840 | 0.000 | 0.00% | 9.840..9.840 | stable | 9.840 |
| `native_mem_post_flush_live_bytes.thread_filter` | 10 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 10 | 0.002 | 0.000 | 3.78% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 10 | 0.055 | 0.000 | 0.72% | 0.054..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 10 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 10 | 8.707 | 0.000 | 0.00% | stable | 8.248 | 0.459 |
| internal | 10 | 2.169 | 0.005 | 0.22% | stable | 1.632 | 0.537 |
| thread | 10 | 1.064 | 0.053 | 4.96% | stable | 1.080 | -0.016 |
| symbol | 10 | 1.965 | 0.000 | 0.00% | stable | 1.944 | 0.021 |
| code | 10 | 51.353 | 0.105 | 0.20% | stable | 44.580 | 6.773 |
| metaspace | 10 | 22.049 | 0.035 | 0.16% | stable | 21.839 | 0.210 |
| arena_chunk | 10 | 1.071 | 0.252 | 23.56% | noisy | 1.083 | -0.012 |
| native_memory_tracking | 10 | 2.631 | 0.011 | 0.43% | stable | 2.350 | 0.281 |
| total | 10 | 669.396 | 0.324 | 0.05% | stable | 661.096 | 8.300 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 10 | 693.315 | 3.802 |
| counters | RssAnon | 10 | 669.218 | 3.803 |
| nmt | VmRSS | 10 | 697.778 | 1.180 |
| nmt | RssAnon | 10 | 673.681 | 1.181 |
| noprof | VmRSS | 3 | 662.134 | 0.992 |
| noprof | RssAnon | 3 | 642.077 | 0.983 |
