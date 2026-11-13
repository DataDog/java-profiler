# Phase 0: memcheck noise

- profiler-commit: `adbd3fff8eccc3536f35fa87c4023378a9e281cc`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `4`
- runs: counters=9, nmt=9, noprof=9

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.021 | 0.000 | 1.74% | 0.020..0.021 | stable | 0.020 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.040 | 0.001 | 1.32% | 0.040..0.041 | stable | 0.040 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.49% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 24.963 | 0.006 | 0.03% | 24.959..24.971 | stable | 24.967 |
| `native_mem_live_bytes.calltrace` | 3 | 3.703 | 0.006 | 0.17% | 3.696..3.707 | stable | 3.709 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.797 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.096 | 0.005 | 5.35% | 0.091..0.101 | stable | 0.099 |
| `native_mem_live_bytes.method_map` | 3 | 0.242 | 0.003 | 1.32% | 0.240..0.246 | stable | 0.242 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.92% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 26.127 | 0.010 | 0.04% | 26.116..26.137 | stable | 26.122 |
| `native_mem_max_bytes.calltrace` | 3 | 4.865 | 0.006 | 0.12% | 4.860..4.871 | stable | 4.863 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.797 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.096 | 0.005 | 5.35% | 0.091..0.101 | stable | 0.099 |
| `native_mem_max_bytes.method_map` | 3 | 0.242 | 0.003 | 1.32% | 0.240..0.246 | stable | 0.242 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.09% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_observed_total_bytes` | 3 | 24.963 | 0.006 | 0.03% | 24.959..24.971 | stable | 24.967 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.562 | 0.000 | 0.01% | 3.562..3.563 | stable | 3.562 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.041 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.096 | 0.005 | 5.35% | 0.091..0.101 | stable | 0.099 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.242 | 0.003 | 1.32% | 0.240..0.246 | stable | 0.242 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 3.09% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.882 | 0.001 | 0.01% | stable | 4.524 | 0.358 |
| internal | 3 | 1.823 | 0.003 | 0.19% | stable | 1.463 | 0.360 |
| thread | 3 | 0.964 | 0.002 | 0.23% | stable | 0.945 | 0.019 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 18.186 | 0.102 | 0.56% | stable | 16.869 | 1.316 |
| metaspace | 3 | 11.517 | 0.000 | 0.00% | stable | 11.266 | 0.251 |
| arena_chunk | 3 | 0.823 | 0.018 | 2.23% | stable | 0.770 | 0.052 |
| native_memory_tracking | 3 | 1.295 | 0.002 | 0.19% | stable | 1.088 | 0.207 |
| total | 3 | 618.551 | 0.126 | 0.02% | stable | 615.964 | 2.588 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 632.331 | 0.643 |
| counters | RssAnon | 3 | 605.672 | 0.530 |
| nmt | VmRSS | 3 | 634.361 | 1.199 |
| nmt | RssAnon | 3 | 607.760 | 1.181 |
| noprof | VmRSS | 3 | 605.621 | 2.217 |
| noprof | RssAnon | 3 | 583.092 | 2.294 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.117 | 0.001 | 0.46% | 0.116..0.118 | stable | 0.118 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.160 | 0.001 | 0.38% | 0.159..0.160 | stable | 0.160 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 1.46% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 26.639 | 0.008 | 0.03% | 26.632..26.647 | stable | 26.649 |
| `native_mem_live_bytes.calltrace` | 3 | 4.405 | 0.003 | 0.06% | 4.402..4.407 | stable | 4.403 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.353 | 0.002 | 0.67% | 0.350..0.355 | stable | 0.359 |
| `native_mem_live_bytes.method_map` | 3 | 0.958 | 0.004 | 0.39% | 0.954..0.962 | stable | 0.962 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 1.86% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.82% | 0.053..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 28.633 | 0.013 | 0.05% | 28.620..28.646 | stable | 28.666 |
| `native_mem_max_bytes.calltrace` | 3 | 6.391 | 0.008 | 0.12% | 6.382..6.398 | stable | 6.413 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.353 | 0.002 | 0.67% | 0.350..0.355 | stable | 0.359 |
| `native_mem_max_bytes.method_map` | 3 | 0.958 | 0.004 | 0.39% | 0.954..0.962 | stable | 0.962 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.639 | 0.008 | 0.03% | 26.632..26.647 | stable | 26.649 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.729 | 0.001 | 0.01% | 3.729..3.730 | stable | 3.730 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.353 | 0.002 | 0.67% | 0.350..0.355 | stable | 0.359 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.958 | 0.004 | 0.39% | 0.954..0.962 | stable | 0.962 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.399 | 0.001 | 0.00% | stable | 65.459 | 2.940 |
| internal | 3 | 6.541 | 0.003 | 0.05% | stable | 3.317 | 3.224 |
| thread | 3 | 0.937 | 0.002 | 0.24% | stable | 0.933 | 0.004 |
| symbol | 3 | 5.878 | 0.000 | 0.00% | stable | 5.857 | 0.021 |
| code | 3 | 57.576 | 0.101 | 0.18% | stable | 52.321 | 5.255 |
| metaspace | 3 | 115.907 | 0.938 | 0.81% | stable | 114.972 | 0.935 |
| arena_chunk | 3 | 0.692 | 0.018 | 2.61% | stable | 0.702 | -0.011 |
| native_memory_tracking | 3 | 10.738 | 0.038 | 0.36% | stable | 8.640 | 2.098 |
| total | 3 | 849.250 | 1.184 | 0.14% | stable | 835.157 | 14.093 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 870.579 | 1.762 |
| counters | RssAnon | 3 | 843.930 | 1.804 |
| nmt | VmRSS | 3 | 883.578 | 3.667 |
| nmt | RssAnon | 3 | 856.924 | 3.684 |
| noprof | VmRSS | 3 | 847.566 | 2.721 |
| noprof | RssAnon | 3 | 825.079 | 2.828 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.058 | 0.000 | 0.27% | 0.058..0.058 | stable | 0.058 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.084 | 0.000 | 0.51% | 0.084..0.085 | stable | 0.084 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.000 | 0.000 | 2.73% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 3 | 23.628 | 0.013 | 0.05% | 23.619..23.642 | stable | 23.616 |
| `native_mem_live_bytes.calltrace` | 3 | 4.293 | 0.003 | 0.07% | 4.290..4.296 | stable | 4.286 |
| `native_mem_live_bytes.dictionary` | 3 | 4.559 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.152 | 0.003 | 2.08% | 0.149..0.155 | stable | 0.154 |
| `native_mem_live_bytes.method_map` | 3 | 0.505 | 0.003 | 0.51% | 0.502..0.507 | stable | 0.504 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.333 | 0.011 | 0.04% | 25.325..25.346 | stable | 25.333 |
| `native_mem_max_bytes.calltrace` | 3 | 5.446 | 0.002 | 0.03% | 5.445..5.449 | stable | 5.448 |
| `native_mem_max_bytes.dictionary` | 3 | 5.101 | 0.007 | 0.14% | 5.097..5.109 | stable | 5.098 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.152 | 0.003 | 2.08% | 0.149..0.155 | stable | 0.154 |
| `native_mem_max_bytes.method_map` | 3 | 0.505 | 0.003 | 0.51% | 0.502..0.507 | stable | 0.504 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.003 | 0.000 | 1.52% | 0.003..0.003 | stable | 0.003 |
| `native_mem_max_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.628 | 0.013 | 0.05% | 23.619..23.642 | stable | 23.616 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.000 | 0.00% | 3.624..3.625 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.557 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.152 | 0.003 | 2.08% | 0.149..0.155 | stable | 0.154 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.505 | 0.003 | 0.51% | 0.502..0.507 | stable | 0.504 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.003 | 0.000 | 1.52% | 0.003..0.003 | stable | 0.003 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.055 | 0.000 | 0.00% | 0.055..0.055 | stable | 0.055 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.710 | 0.001 | 0.01% | stable | 8.250 | 0.460 |
| internal | 3 | 2.233 | 0.004 | 0.18% | stable | 1.627 | 0.606 |
| thread | 3 | 0.971 | 0.005 | 0.46% | stable | 0.972 | -0.000 |
| symbol | 3 | 1.965 | 0.000 | 0.00% | stable | 1.944 | 0.021 |
| code | 3 | 30.075 | 0.132 | 0.44% | stable | 26.658 | 3.417 |
| metaspace | 3 | 22.023 | 0.017 | 0.08% | stable | 21.833 | 0.191 |
| arena_chunk | 3 | 0.956 | 0.381 | 39.83% | noisy | 1.416 | -0.460 |
| native_memory_tracking | 3 | 2.233 | 0.002 | 0.10% | stable | 1.936 | 0.297 |
| total | 3 | 647.633 | 0.256 | 0.04% | stable | 642.779 | 4.854 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 671.415 | 2.713 |
| counters | RssAnon | 3 | 644.626 | 2.690 |
| nmt | VmRSS | 3 | 675.893 | 2.405 |
| nmt | RssAnon | 3 | 649.180 | 2.419 |
| noprof | VmRSS | 3 | 643.395 | 2.253 |
| noprof | RssAnon | 3 | 620.780 | 2.261 |
