# Phase 0: memcheck noise

- profiler-commit: `7cd55c5ec9ca24e5e6eb59cd76b052a94f6e5138`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS` (jdk.txt captured the JAVA_TOOL_OPTIONS line; version from runner.txt)
- cpus: `72`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.023 | 0.000 | 1.37% | 0.023..0.024 | stable | 0.023 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.046 | 0.001 | 1.52% | 0.045..0.046 | stable | 0.046 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 9.95% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 24.721 | 0.007 | 0.03% | 24.713..24.727 | stable | 24.732 |
| `native_mem_live_bytes.calltrace` | 3 | 3.699 | 0.006 | 0.15% | 3.694..3.705 | stable | 3.698 |
| `native_mem_live_bytes.dictionary` | 3 | 6.801 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.104 | 0.003 | 2.56% | 0.101..0.106 | stable | 0.109 |
| `native_mem_live_bytes.method_map` | 3 | 0.274 | 0.004 | 1.52% | 0.269..0.277 | stable | 0.277 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.005 | 0.001 | 11.04% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 25.944 | 0.010 | 0.04% | 25.933..25.954 | stable | 25.954 |
| `native_mem_max_bytes.calltrace` | 3 | 4.910 | 0.005 | 0.09% | 4.904..4.913 | stable | 4.910 |
| `native_mem_max_bytes.dictionary` | 3 | 6.801 | 0.003 | 0.05% | 6.797..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.104 | 0.003 | 2.56% | 0.101..0.106 | stable | 0.109 |
| `native_mem_max_bytes.method_map` | 3 | 0.274 | 0.004 | 1.52% | 0.269..0.277 | stable | 0.277 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.000 | 3.64% | 0.007..0.008 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_observed_total_bytes` | 3 | 24.721 | 0.007 | 0.03% | 24.713..24.727 | stable | 24.732 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.569 | 0.000 | 0.01% | 3.569..3.569 | stable | 3.569 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.049 | 0.007 | 0.11% | 6.041..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.104 | 0.003 | 2.56% | 0.101..0.106 | stable | 0.109 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.274 | 0.004 | 1.52% | 0.269..0.277 | stable | 0.277 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.008 | 0.000 | 3.64% | 0.007..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.057 | 0.000 | 0.77% | 0.057..0.058 | stable | 0.059 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.873 | 0.018 | 0.38% | stable | 4.569 | 0.303 |
| internal | 3 | 1.018 | 0.005 | 0.53% | stable | 0.640 | 0.378 |
| thread | 3 | 1.812 | 0.138 | 7.59% | noisy | 1.676 | 0.136 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 23.118 | 1.461 | 6.32% | noisy | 21.131 | 1.988 |
| metaspace | 3 | 11.495 | 0.036 | 0.31% | stable | 11.266 | 0.229 |
| arena_chunk | 3 | 0.694 | 1.036 | 149.21% | noisy | 0.002 | 0.692 |
| native_memory_tracking | 3 | 1.555 | 0.048 | 3.06% | stable | 1.330 | 0.225 |
| total | 3 | 721.703 | 12.156 | 1.68% | banded | 711.577 | 10.126 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 656.428 | 8.686 |
| counters | RssAnon | 3 | 629.743 | 8.699 |
| nmt | VmRSS | 3 | 657.909 | 2.296 |
| nmt | RssAnon | 3 | 631.306 | 2.250 |
| noprof | VmRSS | 1 | 639.402 | 0.000 |
| noprof | RssAnon | 1 | 617.082 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.107 | 0.001 | 1.30% | 0.106..0.108 | stable | 0.109 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.153 | 0.002 | 1.52% | 0.152..0.156 | stable | 0.155 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 11.84% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.341 | 0.052 | 0.20% | 26.281..26.375 | stable | 26.366 |
| `native_mem_live_bytes.calltrace` | 3 | 4.428 | 0.040 | 0.91% | 4.385..4.464 | stable | 4.440 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.328 | 0.004 | 1.09% | 0.324..0.331 | stable | 0.333 |
| `native_mem_live_bytes.method_map` | 3 | 0.920 | 0.014 | 1.52% | 0.910..0.936 | stable | 0.927 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.009 | 0.001 | 10.17% | 0.008..0.010 | stable | 0.009 |
| `native_mem_live_bytes.thread_local` | 3 | 0.068 | 0.003 | 4.05% | 0.066..0.071 | stable | 0.069 |
| `native_mem_max_bytes` | 3 | 28.184 | 0.042 | 0.15% | 28.159..28.232 | stable | 28.231 |
| `native_mem_max_bytes.calltrace` | 3 | 6.260 | 0.029 | 0.46% | 6.236..6.292 | stable | 6.293 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.328 | 0.004 | 1.09% | 0.324..0.331 | stable | 0.333 |
| `native_mem_max_bytes.method_map` | 3 | 0.920 | 0.014 | 1.52% | 0.910..0.936 | stable | 0.927 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.001 | 10.17% | 0.008..0.010 | stable | 0.009 |
| `native_mem_max_bytes.thread_local` | 3 | 0.071 | 0.003 | 4.46% | 0.069..0.075 | stable | 0.073 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.341 | 0.052 | 0.20% | 26.281..26.375 | stable | 26.366 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.723 | 0.001 | 0.04% | 3.722..3.725 | stable | 3.725 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.328 | 0.004 | 1.09% | 0.324..0.331 | stable | 0.333 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.920 | 0.014 | 1.52% | 0.910..0.936 | stable | 0.927 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 7.81% | 0.006..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.064 | 0.002 | 2.47% | 0.063..0.066 | stable | 0.064 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.418 | 0.004 | 0.01% | stable | 65.478 | 2.941 |
| internal | 3 | 6.798 | 0.011 | 0.16% | stable | 3.589 | 3.209 |
| thread | 3 | 2.181 | 0.206 | 9.44% | noisy | 2.187 | -0.005 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 65.693 | 1.022 | 1.56% | banded | 58.638 | 7.055 |
| metaspace | 3 | 117.810 | 0.936 | 0.79% | stable | 116.401 | 1.409 |
| arena_chunk | 3 | 3.210 | 1.166 | 36.33% | noisy | 3.838 | -0.628 |
| native_memory_tracking | 3 | 12.232 | 0.039 | 0.32% | stable | 10.114 | 2.118 |
| total | 3 | 960.484 | 19.951 | 2.08% | banded | 942.263 | 18.221 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 916.717 | 12.540 |
| counters | RssAnon | 3 | 889.960 | 12.750 |
| nmt | VmRSS | 3 | 929.152 | 12.415 |
| nmt | RssAnon | 3 | 902.264 | 12.317 |
| noprof | VmRSS | 1 | 874.840 | 0.000 |
| noprof | RssAnon | 1 | 852.594 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 1.05% | 0.087..0.089 | stable | 0.089 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.002 | 2.48% | 0.072..0.075 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 10.60% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.073 | 0.068 | 0.26% | 26.022..26.150 | stable | 26.047 |
| `native_mem_live_bytes.calltrace` | 3 | 4.352 | 0.049 | 1.14% | 4.321..4.409 | stable | 4.324 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.133 | 0.009 | 7.07% | 0.122..0.140 | stable | 0.133 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.441 | 0.011 | 2.48% | 0.430..0.452 | stable | 0.442 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.001 | 11.72% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.670 | 0.047 | 0.17% | 27.637..27.724 | stable | 27.667 |
| `native_mem_max_bytes.calltrace` | 3 | 5.927 | 0.031 | 0.52% | 5.906..5.962 | stable | 5.923 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.133 | 0.009 | 7.07% | 0.122..0.140 | stable | 0.133 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.441 | 0.011 | 2.48% | 0.430..0.452 | stable | 0.442 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.011 | 0.001 | 10.62% | 0.010..0.012 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.073 | 0.068 | 0.26% | 26.022..26.150 | stable | 26.047 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.03% | 3.693..3.695 | stable | 3.695 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.133 | 0.009 | 7.07% | 0.122..0.140 | stable | 0.133 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.441 | 0.011 | 2.48% | 0.430..0.452 | stable | 0.442 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.011 | 0.001 | 10.62% | 0.010..0.012 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.060 | 0.003 | 4.38% | 0.059..0.063 | stable | 0.059 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.856 | 0.007 | 0.15% | stable | 4.575 | 0.281 |
| internal | 3 | 1.043 | 0.007 | 0.62% | stable | 0.635 | 0.408 |
| thread | 3 | 1.724 | 0.089 | 5.16% | noisy | 1.513 | 0.212 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 21.954 | 0.601 | 2.74% | banded | 21.594 | 0.360 |
| metaspace | 3 | 11.495 | 0.036 | 0.31% | stable | 11.328 | 0.167 |
| arena_chunk | 3 | 0.695 | 1.037 | 149.23% | noisy | 0.003 | 0.692 |
| native_memory_tracking | 3 | 1.519 | 0.019 | 1.23% | stable | 1.345 | 0.174 |
| total | 3 | 719.697 | 19.443 | 2.70% | banded | 705.911 | 13.785 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 657.163 | 6.659 |
| counters | RssAnon | 3 | 630.475 | 6.757 |
| nmt | VmRSS | 3 | 660.805 | 10.291 |
| nmt | RssAnon | 3 | 634.059 | 10.044 |
| noprof | VmRSS | 1 | 647.535 | 0.000 |
| noprof | RssAnon | 1 | 625.254 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 31.65% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 41.66% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 0.51% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.135 | 0.005 | 0.02% | 22.129..22.139 | stable | 22.136 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.006 | 0.003 | 45.53% | 0.003..0.008 | stable | 0.007 |
| `native_mem_live_bytes.method_map` | 3 | 0.006 | 0.003 | 41.42% | 0.003..0.008 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.031 | 0.000 | 1.03% | 0.031..0.032 | stable | 0.032 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.170 | 0.015 | 0.07% | 23.153..23.179 | stable | 23.164 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.002 | 0.03% | 4.552..4.555 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.572 | 0.009 | 0.19% | 4.562..4.577 | stable | 4.566 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.006 | 0.003 | 45.53% | 0.003..0.008 | stable | 0.007 |
| `native_mem_max_bytes.method_map` | 3 | 0.006 | 0.003 | 41.42% | 0.003..0.008 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.032 | 0.000 | 0.90% | 0.031..0.032 | stable | 0.032 |
| `native_mem_max_bytes.thread_local` | 3 | 0.208 | 0.000 | 0.00% | 0.208..0.208 | stable | 0.208 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.136 | 0.004 | 0.02% | 22.132..22.139 | stable | 22.136 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.006 | 0.003 | 45.53% | 0.003..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.006 | 0.003 | 41.42% | 0.003..0.008 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.032 | 0.000 | 0.90% | 0.031..0.032 | stable | 0.032 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.395 | 0.001 | 0.25% | stable | 0.282 | 0.112 |
| internal | 3 | 0.764 | 0.004 | 0.48% | stable | 0.604 | 0.161 |
| thread | 3 | 22.311 | 0.043 | 0.19% | stable | 22.267 | 0.044 |
| symbol | 3 | 1.133 | 0.001 | 0.05% | stable | 1.119 | 0.014 |
| code | 3 | 7.444 | 0.001 | 0.01% | stable | 7.437 | 0.007 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.008 | 0.001 | 6.93% | stable | 0.008 | 0.000 |
| native_memory_tracking | 3 | 0.349 | 0.003 | 0.85% | stable | 0.300 | 0.049 |
| total | 3 | 703.780 | 8.477 | 1.20% | banded | 695.556 | 8.224 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 616.094 | 0.312 |
| counters | RssAnon | 3 | 589.548 | 0.238 |
| nmt | VmRSS | 3 | 616.303 | 0.226 |
| nmt | RssAnon | 3 | 589.911 | 0.300 |
| noprof | VmRSS | 1 | 591.926 | 0.000 |
| noprof | RssAnon | 1 | 570.523 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.000 | 0.69% | 0.055..0.056 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.001 | 1.37% | 0.074..0.076 | stable | 0.075 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 8.98% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 23.331 | 0.010 | 0.04% | 23.319..23.337 | stable | 23.300 |
| `native_mem_live_bytes.calltrace` | 3 | 4.329 | 0.009 | 0.21% | 4.321..4.339 | stable | 4.315 |
| `native_mem_live_bytes.dictionary` | 3 | 4.565 | 0.010 | 0.22% | 4.553..4.570 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.70% | 0.128..0.137 | stable | 0.132 |
| `native_mem_live_bytes.method_map` | 3 | 0.452 | 0.006 | 1.37% | 0.445..0.458 | stable | 0.448 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.001 | 10.31% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.062 | 0.002 | 2.58% | 0.060..0.063 | stable | 0.062 |
| `native_mem_max_bytes` | 3 | 24.995 | 0.023 | 0.09% | 24.970..25.014 | stable | 24.970 |
| `native_mem_max_bytes.calltrace` | 3 | 5.432 | 0.006 | 0.11% | 5.425..5.436 | stable | 5.422 |
| `native_mem_max_bytes.dictionary` | 3 | 5.103 | 0.009 | 0.17% | 5.094..5.111 | stable | 5.094 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.70% | 0.128..0.137 | stable | 0.132 |
| `native_mem_max_bytes.method_map` | 3 | 0.452 | 0.006 | 1.37% | 0.445..0.458 | stable | 0.448 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.001 | 10.22% | 0.008..0.010 | stable | 0.009 |
| `native_mem_max_bytes.thread_local` | 3 | 0.074 | 0.003 | 3.63% | 0.071..0.076 | stable | 0.074 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.331 | 0.010 | 0.04% | 23.319..23.337 | stable | 23.300 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.626 | 0.000 | 0.01% | 3.625..3.626 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.561 | 0.007 | 0.15% | 4.553..4.565 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.133 | 0.005 | 3.70% | 0.128..0.137 | stable | 0.132 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.452 | 0.006 | 1.37% | 0.445..0.458 | stable | 0.448 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.009 | 0.001 | 10.22% | 0.008..0.010 | stable | 0.009 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.066 | 0.002 | 2.91% | 0.064..0.068 | stable | 0.066 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.728 | 0.002 | 0.02% | stable | 8.270 | 0.459 |
| internal | 3 | 1.430 | 0.006 | 0.44% | stable | 0.842 | 0.589 |
| thread | 3 | 1.870 | 0.091 | 4.87% | banded | 1.902 | -0.032 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 53.430 | 0.362 | 0.68% | stable | 46.921 | 6.509 |
| metaspace | 3 | 21.948 | 0.005 | 0.02% | stable | 21.753 | 0.195 |
| arena_chunk | 3 | 0.003 | 0.001 | 21.65% | stable | 0.003 | -0.000 |
| native_memory_tracking | 3 | 2.645 | 0.004 | 0.13% | stable | 2.327 | 0.317 |
| total | 3 | 756.836 | 12.848 | 1.70% | banded | 748.121 | 8.715 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 717.332 | 0.807 |
| counters | RssAnon | 3 | 690.604 | 0.955 |
| nmt | VmRSS | 3 | 723.391 | 3.836 |
| nmt | RssAnon | 3 | 696.335 | 3.847 |
| noprof | VmRSS | 1 | 688.062 | 0.000 |
| noprof | RssAnon | 1 | 665.535 | 0.000 |
