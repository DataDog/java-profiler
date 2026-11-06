# Phase 0: memcheck noise

- profiler-commit: `7cd55c5ec9ca24e5e6eb59cd76b052a94f6e5138`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS` (jdk.txt captured the JAVA_TOOL_OPTIONS line; version from runner.txt)
- cpus: `68`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.024 | 0.000 | 1.90% | 0.023..0.024 | stable | 0.023 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.046 | 0.001 | 1.83% | 0.046..0.047 | stable | 0.046 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 10.92% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 24.734 | 0.003 | 0.01% | 24.732..24.736 | stable | 24.733 |
| `native_mem_live_bytes.calltrace` | 3 | 3.700 | 0.008 | 0.21% | 3.693..3.708 | stable | 3.706 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.109 | 0.005 | 4.77% | 0.103..0.113 | stable | 0.104 |
| `native_mem_live_bytes.method_map` | 3 | 0.277 | 0.005 | 1.83% | 0.273..0.283 | stable | 0.276 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.001 | 12.03% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 3 | 25.958 | 0.015 | 0.06% | 25.942..25.972 | stable | 25.946 |
| `native_mem_max_bytes.calltrace` | 3 | 4.913 | 0.007 | 0.14% | 4.907..4.920 | stable | 4.908 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.109 | 0.005 | 4.77% | 0.103..0.113 | stable | 0.104 |
| `native_mem_max_bytes.method_map` | 3 | 0.277 | 0.005 | 1.83% | 0.273..0.283 | stable | 0.276 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.001 | 10.02% | 0.007..0.009 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_observed_total_bytes` | 3 | 24.734 | 0.003 | 0.01% | 24.732..24.736 | stable | 24.733 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.569 | 0.000 | 0.01% | 3.569..3.570 | stable | 3.569 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.109 | 0.005 | 4.77% | 0.103..0.113 | stable | 0.104 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.277 | 0.005 | 1.83% | 0.273..0.283 | stable | 0.276 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.008 | 0.001 | 10.02% | 0.007..0.009 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.058 | 0.001 | 1.32% | 0.057..0.059 | stable | 0.058 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.847 | 0.004 | 0.08% | stable | 4.592 | 0.255 |
| internal | 3 | 1.012 | 0.008 | 0.77% | stable | 0.638 | 0.374 |
| thread | 3 | 1.710 | 0.095 | 5.57% | noisy | 1.709 | 0.001 |
| symbol | 3 | 1.594 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 21.321 | 0.199 | 0.93% | stable | 22.651 | -1.331 |
| metaspace | 3 | 11.453 | 0.000 | 0.00% | stable | 11.266 | 0.188 |
| arena_chunk | 3 | 0.767 | 1.162 | 151.49% | noisy | 0.002 | 0.765 |
| native_memory_tracking | 3 | 1.488 | 0.013 | 0.86% | stable | 1.381 | 0.107 |
| total | 3 | 725.771 | 18.514 | 2.55% | banded | 707.185 | 18.587 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 650.917 | 1.384 |
| counters | RssAnon | 3 | 624.148 | 1.412 |
| nmt | VmRSS | 3 | 666.428 | 2.890 |
| nmt | RssAnon | 3 | 639.790 | 2.933 |
| noprof | VmRSS | 1 | 638.902 | 0.000 |
| noprof | RssAnon | 1 | 616.469 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.111 | 0.003 | 3.09% | 0.107..0.114 | stable | 0.106 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.156 | 0.003 | 2.04% | 0.153..0.159 | stable | 0.152 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 8.69% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.367 | 0.038 | 0.14% | 26.324..26.395 | stable | 26.360 |
| `native_mem_live_bytes.calltrace` | 3 | 4.434 | 0.025 | 0.56% | 4.408..4.458 | stable | 4.454 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.337 | 0.006 | 1.90% | 0.332..0.344 | stable | 0.326 |
| `native_mem_live_bytes.method_map` | 3 | 0.934 | 0.019 | 2.03% | 0.917..0.954 | stable | 0.912 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.009 | 0.001 | 9.27% | 0.008..0.010 | stable | 0.010 |
| `native_mem_live_bytes.thread_local` | 3 | 0.067 | 0.001 | 1.32% | 0.066..0.067 | stable | 0.070 |
| `native_mem_max_bytes` | 3 | 28.283 | 0.055 | 0.19% | 28.228..28.338 | stable | 28.182 |
| `native_mem_max_bytes.calltrace` | 3 | 6.335 | 0.035 | 0.55% | 6.296..6.362 | stable | 6.264 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.337 | 0.006 | 1.90% | 0.332..0.344 | stable | 0.326 |
| `native_mem_max_bytes.method_map` | 3 | 0.934 | 0.019 | 2.03% | 0.917..0.954 | stable | 0.912 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.009 | 0.001 | 9.27% | 0.008..0.010 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.073 | 0.003 | 4.21% | 0.069..0.076 | stable | 0.075 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.367 | 0.038 | 0.14% | 26.324..26.395 | stable | 26.360 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.727 | 0.003 | 0.08% | 3.724..3.730 | stable | 3.723 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.337 | 0.006 | 1.90% | 0.332..0.344 | stable | 0.326 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.934 | 0.019 | 2.03% | 0.917..0.954 | stable | 0.912 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 9.81% | 0.007..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.064 | 0.002 | 2.76% | 0.062..0.065 | stable | 0.065 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.421 | 0.005 | 0.01% | stable | 65.478 | 2.944 |
| internal | 3 | 6.801 | 0.010 | 0.14% | stable | 3.588 | 3.214 |
| thread | 3 | 2.316 | 0.154 | 6.63% | noisy | 2.110 | 0.206 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.856 | 0.021 |
| code | 3 | 65.812 | 0.916 | 1.39% | banded | 57.484 | 8.328 |
| metaspace | 3 | 116.694 | 0.285 | 0.24% | stable | 116.128 | 0.566 |
| arena_chunk | 3 | 3.327 | 1.158 | 34.80% | noisy | 0.003 | 3.324 |
| native_memory_tracking | 3 | 12.188 | 0.019 | 0.16% | stable | 10.077 | 2.111 |
| total | 3 | 973.244 | 18.233 | 1.87% | banded | 930.871 | 42.373 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 921.809 | 12.656 |
| counters | RssAnon | 3 | 894.807 | 12.705 |
| nmt | VmRSS | 3 | 932.639 | 6.567 |
| nmt | RssAnon | 3 | 905.686 | 6.387 |
| noprof | VmRSS | 1 | 900.234 | 0.000 |
| noprof | RssAnon | 1 | 877.703 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.087 | 0.001 | 1.21% | 0.086..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.074 | 0.001 | 0.90% | 0.073..0.075 | stable | 0.073 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 0.59% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.053 | 0.018 | 0.07% | 26.032..26.067 | stable | 26.053 |
| `native_mem_live_bytes.calltrace` | 3 | 4.330 | 0.012 | 0.28% | 4.316..4.339 | stable | 4.331 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.132 | 0.003 | 2.53% | 0.129..0.136 | stable | 0.133 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.443 | 0.004 | 0.90% | 0.439..0.447 | stable | 0.441 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.000 | 0.64% | 0.006..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 27.654 | 0.021 | 0.08% | 27.634..27.675 | stable | 27.661 |
| `native_mem_max_bytes.calltrace` | 3 | 5.907 | 0.015 | 0.26% | 5.895..5.925 | stable | 5.917 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.132 | 0.003 | 2.53% | 0.129..0.136 | stable | 0.133 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.443 | 0.004 | 0.90% | 0.439..0.447 | stable | 0.441 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.012 | 0.001 | 6.29% | 0.012..0.013 | stable | 0.012 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.053 | 0.018 | 0.07% | 26.032..26.067 | stable | 26.053 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.693 | 0.001 | 0.03% | 3.692..3.694 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.132 | 0.003 | 2.53% | 0.129..0.136 | stable | 0.133 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.443 | 0.004 | 0.90% | 0.439..0.447 | stable | 0.441 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.012 | 0.001 | 6.29% | 0.012..0.013 | stable | 0.012 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.060 | 0.001 | 1.47% | 0.060..0.061 | stable | 0.060 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.867 | 0.006 | 0.12% | stable | 4.593 | 0.274 |
| internal | 3 | 1.052 | 0.002 | 0.19% | stable | 0.651 | 0.400 |
| thread | 3 | 1.901 | 0.085 | 4.45% | banded | 1.895 | 0.007 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 22.615 | 0.436 | 1.93% | banded | 22.516 | 0.100 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.695 | 1.036 | 149.11% | noisy | 1.986 | -1.291 |
| native_memory_tracking | 3 | 1.544 | 0.017 | 1.08% | stable | 1.387 | 0.157 |
| total | 3 | 738.209 | 3.417 | 0.46% | stable | 739.702 | -1.493 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 653.902 | 1.256 |
| counters | RssAnon | 3 | 626.922 | 1.268 |
| nmt | VmRSS | 3 | 658.605 | 1.418 |
| nmt | RssAnon | 3 | 631.598 | 1.370 |
| noprof | VmRSS | 1 | 642.484 | 0.000 |
| noprof | RssAnon | 1 | 620.324 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 9.96% | 0.000..0.001 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 19.48% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 1.54% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.139 | 0.002 | 0.01% | 22.136..22.141 | stable | 22.136 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.008 | 0.001 | 16.76% | 0.007..0.010 | stable | 0.006 |
| `native_mem_live_bytes.method_map` | 3 | 0.007 | 0.001 | 20.31% | 0.006..0.008 | stable | 0.006 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.88% | 0.031..0.032 | stable | 0.032 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.172 | 0.012 | 0.05% | 23.163..23.186 | stable | 23.166 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.001 | 0.02% | 4.554..4.555 | stable | 4.553 |
| `native_mem_max_bytes.dictionary` | 3 | 4.571 | 0.010 | 0.21% | 4.565..4.582 | stable | 4.568 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.008 | 0.001 | 16.76% | 0.007..0.010 | stable | 0.006 |
| `native_mem_max_bytes.method_map` | 3 | 0.007 | 0.001 | 20.31% | 0.006..0.008 | stable | 0.006 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.87% | 0.031..0.032 | stable | 0.032 |
| `native_mem_max_bytes.thread_local` | 3 | 0.208 | 0.000 | 0.00% | 0.208..0.208 | stable | 0.208 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.139 | 0.002 | 0.01% | 22.136..22.141 | stable | 22.136 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.008 | 0.001 | 16.76% | 0.007..0.010 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.007 | 0.001 | 20.31% | 0.006..0.008 | stable | 0.006 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.87% | 0.031..0.032 | stable | 0.032 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.396 | 0.002 | 0.51% | stable | 0.282 | 0.114 |
| internal | 3 | 0.768 | 0.008 | 1.06% | stable | 0.604 | 0.164 |
| thread | 3 | 22.366 | 0.082 | 0.37% | stable | 22.267 | 0.099 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.444 | 0.000 | 0.00% | stable | 7.437 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.008 | 0.001 | 6.66% | stable | 0.008 | 0.001 |
| native_memory_tracking | 3 | 0.354 | 0.005 | 1.46% | stable | 0.299 | 0.055 |
| total | 3 | 715.711 | 16.826 | 2.35% | banded | 695.220 | 20.491 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 616.193 | 0.569 |
| counters | RssAnon | 3 | 589.872 | 0.605 |
| nmt | VmRSS | 3 | 616.681 | 0.546 |
| nmt | RssAnon | 3 | 590.275 | 0.627 |
| noprof | VmRSS | 1 | 592.047 | 0.000 |
| noprof | RssAnon | 1 | 570.539 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.056 | 0.002 | 3.17% | 0.054..0.058 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.076 | 0.002 | 2.04% | 0.074..0.077 | stable | 0.076 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 9.92% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 23.321 | 0.041 | 0.18% | 23.294..23.368 | stable | 23.277 |
| `native_mem_live_bytes.calltrace` | 3 | 4.324 | 0.030 | 0.69% | 4.303..4.358 | stable | 4.272 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.559 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.135 | 0.002 | 1.83% | 0.132..0.137 | stable | 0.138 |
| `native_mem_live_bytes.method_map` | 3 | 0.453 | 0.009 | 2.04% | 0.447..0.464 | stable | 0.453 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 9.38% | 0.006..0.007 | stable | 0.007 |
| `native_mem_live_bytes.thread_local` | 3 | 0.064 | 0.002 | 2.50% | 0.062..0.065 | stable | 0.064 |
| `native_mem_max_bytes` | 3 | 25.002 | 0.037 | 0.15% | 24.978..25.045 | stable | 25.009 |
| `native_mem_max_bytes.calltrace` | 3 | 5.439 | 0.027 | 0.49% | 5.420..5.470 | stable | 5.440 |
| `native_mem_max_bytes.dictionary` | 3 | 5.095 | 0.001 | 0.02% | 5.094..5.096 | stable | 5.100 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.135 | 0.002 | 1.83% | 0.132..0.137 | stable | 0.138 |
| `native_mem_max_bytes.method_map` | 3 | 0.453 | 0.009 | 2.04% | 0.447..0.464 | stable | 0.453 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.010 | 0.001 | 7.42% | 0.009..0.011 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.076 | 0.001 | 1.73% | 0.075..0.077 | stable | 0.075 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.321 | 0.041 | 0.18% | 23.294..23.368 | stable | 23.277 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.626 | 0.002 | 0.05% | 3.625..3.628 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.557 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.135 | 0.002 | 1.83% | 0.132..0.137 | stable | 0.138 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.453 | 0.009 | 2.04% | 0.447..0.464 | stable | 0.453 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.010 | 0.001 | 7.42% | 0.009..0.011 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.068 | 0.001 | 1.95% | 0.066..0.069 | stable | 0.068 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.731 | 0.002 | 0.02% | stable | 8.270 | 0.461 |
| internal | 3 | 1.443 | 0.012 | 0.81% | stable | 0.840 | 0.604 |
| thread | 3 | 2.046 | 0.097 | 4.75% | banded | 1.934 | 0.113 |
| symbol | 3 | 1.964 | 0.000 | 0.00% | stable | 1.943 | 0.021 |
| code | 3 | 53.638 | 0.079 | 0.15% | stable | 46.917 | 6.721 |
| metaspace | 3 | 21.948 | 0.005 | 0.02% | stable | 21.762 | 0.187 |
| arena_chunk | 3 | 0.507 | 0.871 | 171.87% | noisy | 0.003 | 0.504 |
| native_memory_tracking | 3 | 2.648 | 0.006 | 0.22% | stable | 2.325 | 0.323 |
| total | 3 | 775.380 | 16.901 | 2.18% | banded | 746.068 | 29.312 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 723.208 | 0.982 |
| counters | RssAnon | 3 | 696.277 | 1.229 |
| nmt | VmRSS | 3 | 720.441 | 1.559 |
| nmt | RssAnon | 3 | 693.668 | 1.469 |
| noprof | VmRSS | 1 | 691.168 | 0.000 |
| noprof | RssAnon | 1 | 668.617 | 0.000 |
