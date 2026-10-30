# Phase 0: memcheck noise

- profiler-commit: `7cd55c5ec9ca24e5e6eb59cd76b052a94f6e5138`
- jdk: `openjdk version "21.0.3" 2024-04-16 LTS` (jdk.txt captured the JAVA_TOOL_OPTIONS line; version from runner.txt)
- cpus: `93`
- runs: counters=15, nmt=15, noprof=5

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## allocs

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.022 | 0.001 | 4.00% | 0.022..0.023 | stable | 0.023 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.044 | 0.002 | 4.62% | 0.042..0.046 | stable | 0.044 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 6.01% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 24.730 | 0.017 | 0.07% | 24.712..24.746 | stable | 24.721 |
| `native_mem_live_bytes.calltrace` | 3 | 3.719 | 0.007 | 0.18% | 3.713..3.727 | stable | 3.712 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.102 | 0.004 | 3.60% | 0.098..0.105 | stable | 0.097 |
| `native_mem_live_bytes.method_map` | 3 | 0.262 | 0.012 | 4.62% | 0.253..0.276 | stable | 0.263 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.000 | 7.38% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.82% | 0.053..0.054 | stable | 0.055 |
| `native_mem_max_bytes` | 3 | 25.916 | 0.029 | 0.11% | 25.895..25.949 | stable | 25.917 |
| `native_mem_max_bytes.calltrace` | 3 | 4.895 | 0.013 | 0.26% | 4.887..4.909 | stable | 4.898 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.102 | 0.004 | 3.60% | 0.098..0.105 | stable | 0.097 |
| `native_mem_max_bytes.method_map` | 3 | 0.262 | 0.012 | 4.62% | 0.253..0.276 | stable | 0.263 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.000 | 5.07% | 0.007..0.008 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_observed_total_bytes` | 3 | 24.730 | 0.017 | 0.07% | 24.712..24.746 | stable | 24.721 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.568 | 0.001 | 0.03% | 3.567..3.569 | stable | 3.568 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.102 | 0.004 | 3.60% | 0.098..0.105 | stable | 0.097 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.262 | 0.012 | 4.62% | 0.253..0.276 | stable | 0.263 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.008 | 0.000 | 5.07% | 0.007..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.061 | 0.001 | 1.44% | 0.060..0.062 | stable | 0.061 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.858 | 0.012 | 0.24% | stable | 4.587 | 0.271 |
| internal | 3 | 1.005 | 0.007 | 0.69% | stable | 0.649 | 0.355 |
| thread | 3 | 1.791 | 0.138 | 7.69% | noisy | 1.823 | -0.033 |
| symbol | 3 | 1.595 | 0.000 | 0.00% | stable | 1.573 | 0.021 |
| code | 3 | 22.085 | 0.841 | 3.81% | banded | 22.188 | -0.103 |
| metaspace | 3 | 11.519 | 0.005 | 0.04% | stable | 11.266 | 0.253 |
| arena_chunk | 3 | 0.097 | 0.001 | 1.54% | stable | 0.003 | 0.094 |
| native_memory_tracking | 3 | 1.516 | 0.028 | 1.83% | stable | 1.368 | 0.148 |
| total | 3 | 719.301 | 15.645 | 2.17% | banded | 735.255 | -15.954 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 656.618 | 11.270 |
| counters | RssAnon | 3 | 629.990 | 11.173 |
| nmt | VmRSS | 3 | 654.207 | 1.121 |
| nmt | RssAnon | 3 | 627.454 | 1.178 |
| noprof | VmRSS | 1 | 644.523 | 0.000 |
| noprof | RssAnon | 1 | 621.906 | 0.000 |

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.124 | 0.008 | 6.22% | 0.116..0.130 | stable | 0.130 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.168 | 0.009 | 5.52% | 0.158..0.175 | stable | 0.174 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 3.43% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.495 | 0.070 | 0.26% | 26.415..26.538 | stable | 26.532 |
| `native_mem_live_bytes.calltrace` | 3 | 4.450 | 0.008 | 0.19% | 4.441..4.458 | stable | 4.438 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.371 | 0.022 | 5.89% | 0.345..0.385 | stable | 0.384 |
| `native_mem_live_bytes.method_map` | 3 | 1.009 | 0.056 | 5.51% | 0.945..1.048 | stable | 1.042 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.008 | 0.000 | 2.76% | 0.007..0.008 | stable | 0.008 |
| `native_mem_live_bytes.thread_local` | 3 | 0.070 | 0.000 | 0.63% | 0.070..0.071 | stable | 0.071 |
| `native_mem_max_bytes` | 3 | 28.620 | 0.233 | 0.81% | 28.352..28.762 | stable | 28.793 |
| `native_mem_max_bytes.calltrace` | 3 | 6.567 | 0.155 | 2.37% | 6.388..6.658 | banded | 6.692 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.371 | 0.022 | 5.89% | 0.345..0.385 | stable | 0.384 |
| `native_mem_max_bytes.method_map` | 3 | 1.009 | 0.056 | 5.51% | 0.945..1.048 | stable | 1.042 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.008 | 0.000 | 2.76% | 0.007..0.008 | stable | 0.008 |
| `native_mem_max_bytes.thread_local` | 3 | 0.070 | 0.000 | 0.63% | 0.070..0.071 | stable | 0.071 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.495 | 0.070 | 0.26% | 26.415..26.538 | stable | 26.532 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.741 | 0.008 | 0.21% | 3.731..3.746 | stable | 3.746 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.371 | 0.022 | 5.89% | 0.345..0.385 | stable | 0.384 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 1.009 | 0.056 | 5.51% | 0.945..1.048 | stable | 1.042 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 8.03% | 0.006..0.008 | stable | 0.007 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.063 | 0.001 | 1.20% | 0.063..0.064 | stable | 0.064 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 68.416 | 0.001 | 0.00% | stable | 65.479 | 2.937 |
| internal | 3 | 6.840 | 0.005 | 0.08% | stable | 3.590 | 3.250 |
| thread | 3 | 2.036 | 0.126 | 6.17% | noisy | 2.156 | -0.120 |
| symbol | 3 | 5.878 | 0.001 | 0.01% | stable | 5.857 | 0.020 |
| code | 3 | 59.961 | 1.207 | 2.01% | banded | 54.069 | 5.891 |
| metaspace | 3 | 115.563 | 0.750 | 0.65% | stable | 114.652 | 0.910 |
| arena_chunk | 3 | 1.073 | 0.969 | 90.27% | noisy | 2.467 | -1.394 |
| native_memory_tracking | 3 | 12.046 | 0.058 | 0.48% | stable | 9.938 | 2.109 |
| total | 3 | 954.461 | 10.389 | 1.09% | banded | 952.489 | 1.972 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 915.009 | 7.245 |
| counters | RssAnon | 3 | 888.180 | 7.279 |
| nmt | VmRSS | 3 | 918.311 | 5.243 |
| nmt | RssAnon | 3 | 891.292 | 5.327 |
| noprof | VmRSS | 1 | 875.598 | 0.000 |
| noprof | RssAnon | 1 | 853.145 | 0.000 |

## mixed

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.088 | 0.001 | 0.65% | 0.087..0.088 | stable | 0.088 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.075 | 0.001 | 1.24% | 0.074..0.075 | stable | 0.075 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 8.07% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 26.098 | 0.056 | 0.22% | 26.062..26.163 | stable | 26.109 |
| `native_mem_live_bytes.calltrace` | 3 | 4.360 | 0.054 | 1.23% | 4.328..4.422 | stable | 4.367 |
| `native_mem_live_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.141 | 0.001 | 0.71% | 0.140..0.142 | stable | 0.142 |
| `native_mem_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_live_bytes.method_map` | 3 | 0.449 | 0.006 | 1.25% | 0.442..0.453 | stable | 0.451 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.006 | 0.000 | 8.92% | 0.005..0.006 | stable | 0.006 |
| `native_mem_live_bytes.thread_local` | 3 | 0.054 | 0.000 | 0.81% | 0.054..0.055 | stable | 0.056 |
| `native_mem_max_bytes` | 3 | 27.687 | 0.026 | 0.09% | 27.658..27.710 | stable | 27.693 |
| `native_mem_max_bytes.calltrace` | 3 | 5.928 | 0.022 | 0.37% | 5.905..5.949 | stable | 5.931 |
| `native_mem_max_bytes.dictionary` | 3 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.141 | 0.001 | 0.71% | 0.140..0.142 | stable | 0.142 |
| `native_mem_max_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_max_bytes.method_map` | 3 | 0.449 | 0.006 | 1.25% | 0.442..0.453 | stable | 0.451 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.011 | 0.002 | 15.95% | 0.009..0.012 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.063 | 0.000 | 0.00% | 0.063..0.063 | stable | 0.063 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 26.098 | 0.056 | 0.22% | 26.062..26.163 | stable | 26.109 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.694 | 0.001 | 0.02% | 3.693..3.695 | stable | 3.694 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.141 | 0.001 | 0.71% | 0.140..0.142 | stable | 0.142 |
| `native_mem_post_flush_live_bytes.liveness` | 3 | 0.500 | 0.000 | 0.00% | 0.500..0.500 | stable | 0.500 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.449 | 0.006 | 1.25% | 0.442..0.453 | stable | 0.451 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.011 | 0.002 | 15.95% | 0.009..0.012 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.061 | 0.001 | 2.16% | 0.060..0.062 | stable | 0.062 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 4.846 | 0.003 | 0.05% | stable | 4.555 | 0.291 |
| internal | 3 | 1.054 | 0.009 | 0.81% | stable | 0.653 | 0.400 |
| thread | 3 | 1.837 | 0.095 | 5.20% | noisy | 1.945 | -0.108 |
| symbol | 3 | 1.594 | 0.001 | 0.04% | stable | 1.573 | 0.021 |
| code | 3 | 21.182 | 0.239 | 1.13% | banded | 19.611 | 1.571 |
| metaspace | 3 | 11.474 | 0.036 | 0.31% | stable | 11.266 | 0.208 |
| arena_chunk | 3 | 0.107 | 0.019 | 17.64% | stable | 0.003 | 0.104 |
| native_memory_tracking | 3 | 1.492 | 0.005 | 0.36% | stable | 1.289 | 0.203 |
| total | 3 | 718.396 | 15.077 | 2.10% | banded | 732.645 | -14.249 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 663.393 | 12.538 |
| counters | RssAnon | 3 | 636.543 | 12.598 |
| nmt | VmRSS | 3 | 659.113 | 7.632 |
| nmt | RssAnon | 3 | 632.130 | 7.581 |
| noprof | VmRSS | 1 | 620.750 | 0.000 |
| noprof | RssAnon | 1 | 598.320 | 0.000 |

## threads

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.000 | 0.000 | 9.12% | 0.000..0.000 | stable | 0.000 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.001 | 0.000 | 13.54% | 0.001..0.001 | stable | 0.001 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.005 | 0.000 | 1.21% | 0.005..0.005 | stable | 0.005 |
| `native_mem_live_bytes` | 3 | 22.141 | 0.002 | 0.01% | 22.139..22.142 | stable | 22.140 |
| `native_mem_live_bytes.calltrace` | 3 | 3.548 | 0.000 | 0.01% | 3.548..3.548 | stable | 3.548 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.010 | 0.001 | 13.27% | 0.008..0.011 | stable | 0.008 |
| `native_mem_live_bytes.method_map` | 3 | 0.007 | 0.001 | 13.54% | 0.006..0.008 | stable | 0.008 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.64% | 0.031..0.032 | stable | 0.032 |
| `native_mem_live_bytes.thread_local` | 3 | 0.206 | 0.000 | 0.00% | 0.206..0.206 | stable | 0.207 |
| `native_mem_max_bytes` | 3 | 23.181 | 0.006 | 0.03% | 23.175..23.186 | stable | 23.179 |
| `native_mem_max_bytes.calltrace` | 3 | 4.554 | 0.000 | 0.01% | 4.554..4.554 | stable | 4.554 |
| `native_mem_max_bytes.dictionary` | 3 | 4.577 | 0.004 | 0.09% | 4.573..4.582 | stable | 4.577 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.010 | 0.001 | 13.27% | 0.008..0.011 | stable | 0.008 |
| `native_mem_max_bytes.method_map` | 3 | 0.007 | 0.001 | 13.54% | 0.006..0.008 | stable | 0.008 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.68% | 0.031..0.032 | stable | 0.032 |
| `native_mem_max_bytes.thread_local` | 3 | 0.208 | 0.000 | 0.21% | 0.208..0.208 | stable | 0.208 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 22.141 | 0.002 | 0.01% | 22.139..22.142 | stable | 22.140 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.546 | 0.000 | 0.00% | 3.546..3.546 | stable | 3.546 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.010 | 0.001 | 13.27% | 0.008..0.011 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.007 | 0.001 | 13.54% | 0.006..0.008 | stable | 0.008 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.032 | 0.001 | 1.68% | 0.031..0.032 | stable | 0.032 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.207 | 0.000 | 0.00% | 0.207..0.207 | stable | 0.207 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 0.396 | 0.002 | 0.51% | stable | 0.285 | 0.111 |
| internal | 3 | 0.770 | 0.008 | 1.08% | stable | 0.614 | 0.155 |
| thread | 3 | 22.356 | 0.078 | 0.35% | stable | 22.390 | -0.033 |
| symbol | 3 | 1.134 | 0.000 | 0.00% | stable | 1.119 | 0.015 |
| code | 3 | 7.443 | 0.000 | 0.00% | stable | 7.436 | 0.008 |
| metaspace | 3 | 0.575 | 0.000 | 0.00% | stable | 0.388 | 0.188 |
| arena_chunk | 3 | 0.008 | 0.001 | 6.66% | stable | 0.009 | -0.000 |
| native_memory_tracking | 3 | 0.346 | 0.003 | 0.91% | stable | 0.305 | 0.042 |
| total | 3 | 713.133 | 15.425 | 2.16% | banded | 719.962 | -6.829 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 615.952 | 0.643 |
| counters | RssAnon | 3 | 589.473 | 0.536 |
| nmt | VmRSS | 3 | 616.311 | 0.522 |
| nmt | RssAnon | 3 | 589.827 | 0.482 |
| noprof | VmRSS | 1 | 592.160 | 0.000 |
| noprof | RssAnon | 1 | 570.855 | 0.000 |

## traces

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 3 | 0.054 | 0.002 | 3.05% | 0.052..0.055 | stable | 0.055 |
| `native_mem_chunk_overhead_bytes.dictionary` | 3 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 3 | 0.073 | 0.002 | 3.05% | 0.071..0.075 | stable | 0.074 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 3 | 0.952 | 0.000 | 0.00% | 0.952..0.952 | stable | 0.952 |
| `native_mem_chunk_overhead_bytes.thread_info` | 3 | 0.001 | 0.000 | 8.59% | 0.001..0.001 | stable | 0.001 |
| `native_mem_live_bytes` | 3 | 23.270 | 0.025 | 0.11% | 23.248..23.297 | stable | 23.291 |
| `native_mem_live_bytes.calltrace` | 3 | 4.285 | 0.004 | 0.10% | 4.280..4.288 | stable | 4.298 |
| `native_mem_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 3 | 0.138 | 0.011 | 7.64% | 0.130..0.150 | stable | 0.141 |
| `native_mem_live_bytes.method_map` | 3 | 0.438 | 0.013 | 3.03% | 0.426..0.453 | stable | 0.443 |
| `native_mem_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 3 | 0.007 | 0.001 | 9.31% | 0.006..0.008 | stable | 0.007 |
| `native_mem_live_bytes.thread_local` | 3 | 0.065 | 0.002 | 2.97% | 0.063..0.066 | stable | 0.065 |
| `native_mem_max_bytes` | 3 | 24.994 | 0.065 | 0.26% | 24.949..25.069 | stable | 25.007 |
| `native_mem_max_bytes.calltrace` | 3 | 5.440 | 0.040 | 0.73% | 5.417..5.486 | stable | 5.451 |
| `native_mem_max_bytes.dictionary` | 3 | 5.098 | 0.004 | 0.08% | 5.095..5.102 | stable | 5.097 |
| `native_mem_max_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 3 | 0.138 | 0.011 | 7.64% | 0.130..0.150 | stable | 0.141 |
| `native_mem_max_bytes.method_map` | 3 | 0.438 | 0.013 | 3.03% | 0.426..0.453 | stable | 0.443 |
| `native_mem_max_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_max_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 3 | 0.010 | 0.001 | 5.64% | 0.010..0.011 | stable | 0.010 |
| `native_mem_max_bytes.thread_local` | 3 | 0.077 | 0.001 | 1.52% | 0.076..0.078 | stable | 0.073 |
| `native_mem_max_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 3 | 23.270 | 0.025 | 0.11% | 23.248..23.297 | stable | 23.291 |
| `native_mem_post_flush_live_bytes.calltrace` | 3 | 3.624 | 0.002 | 0.05% | 3.622..3.625 | stable | 3.625 |
| `native_mem_post_flush_live_bytes.dictionary` | 3 | 4.553 | 0.000 | 0.00% | 4.553..4.553 | stable | 4.553 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 3 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 3 | 0.138 | 0.011 | 7.64% | 0.130..0.150 | stable | 0.141 |
| `native_mem_post_flush_live_bytes.method_map` | 3 | 0.438 | 0.013 | 3.03% | 0.426..0.453 | stable | 0.443 |
| `native_mem_post_flush_live_bytes.native_symbols` | 3 | 12.588 | 0.000 | 0.00% | 12.588..12.588 | stable | 12.588 |
| `native_mem_post_flush_live_bytes.thread_filter` | 3 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 3 | 0.010 | 0.001 | 5.64% | 0.010..0.011 | stable | 0.010 |
| `native_mem_post_flush_live_bytes.thread_local` | 3 | 0.068 | 0.001 | 1.70% | 0.067..0.069 | stable | 0.067 |
| `native_mem_post_flush_live_bytes.wallclock` | 3 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 3 | 8.729 | 0.001 | 0.01% | stable | 8.271 | 0.458 |
| internal | 3 | 1.444 | 0.004 | 0.27% | stable | 0.855 | 0.589 |
| thread | 3 | 2.019 | 0.083 | 4.11% | banded | 2.059 | -0.040 |
| symbol | 3 | 1.964 | 0.001 | 0.03% | stable | 1.943 | 0.021 |
| code | 3 | 50.495 | 4.532 | 8.98% | noisy | 39.441 | 11.053 |
| metaspace | 3 | 21.995 | 0.039 | 0.18% | stable | 21.762 | 0.234 |
| arena_chunk | 3 | 1.009 | 0.871 | 86.35% | noisy | 1.513 | -0.504 |
| native_memory_tracking | 3 | 2.612 | 0.052 | 2.00% | stable | 2.254 | 0.358 |
| total | 3 | 763.201 | 10.691 | 1.40% | banded | 760.460 | 2.742 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 3 | 714.241 | 6.096 |
| counters | RssAnon | 3 | 687.201 | 6.122 |
| nmt | VmRSS | 3 | 715.878 | 3.255 |
| nmt | RssAnon | 3 | 689.128 | 3.334 |
| noprof | VmRSS | 1 | 682.457 | 0.000 |
| noprof | RssAnon | 1 | 659.887 | 0.000 |
