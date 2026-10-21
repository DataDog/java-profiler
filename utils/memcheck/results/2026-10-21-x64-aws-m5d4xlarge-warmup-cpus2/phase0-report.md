# Phase 0: memcheck noise

- profiler-commit: `adbd3fff8eccc3536f35fa87c4023378a9e281cc`
- jdk: `openjdk version "21.0.8" 2025-07-15 LTS`
- cpus: `2`
- runs: counters=6, nmt=6, noprof=3

Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. Values in MiB. Zero-valued metrics omitted.

## classesM

### Profiler counters (counters arm, final recording)

| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |
|---|---|---|---|---|---|---|---|
| `native_mem_chunk_overhead_bytes.calltrace` | 6 | 0.118 | 0.001 | 0.67% | 0.117..0.119 | stable | 0.117 |
| `native_mem_chunk_overhead_bytes.dictionary` | 6 | 0.035 | 0.000 | 0.00% | 0.035..0.035 | stable | 0.035 |
| `native_mem_chunk_overhead_bytes.method_map` | 6 | 0.162 | 0.001 | 0.61% | 0.160..0.163 | stable | 0.161 |
| `native_mem_chunk_overhead_bytes.native_symbols` | 6 | 0.981 | 0.000 | 0.00% | 0.981..0.981 | stable | 0.981 |
| `native_mem_chunk_overhead_bytes.thread_info` | 6 | 0.000 | 0.000 | 2.38% | 0.000..0.000 | stable | 0.000 |
| `native_mem_live_bytes` | 6 | 26.648 | 0.014 | 0.05% | 26.623..26.662 | stable | 26.642 |
| `native_mem_live_bytes.calltrace` | 6 | 4.398 | 0.011 | 0.24% | 4.383..4.409 | stable | 4.399 |
| `native_mem_live_bytes.dictionary` | 6 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_live_bytes.jfr_buffers` | 6 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_live_bytes.line_tables` | 6 | 0.357 | 0.002 | 0.59% | 0.353..0.360 | stable | 0.356 |
| `native_mem_live_bytes.method_map` | 6 | 0.972 | 0.006 | 0.60% | 0.962..0.977 | stable | 0.964 |
| `native_mem_live_bytes.native_symbols` | 6 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_live_bytes.thread_filter` | 6 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_live_bytes.thread_info` | 6 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_live_bytes.thread_local` | 6 | 0.053 | 0.000 | 0.00% | 0.053..0.053 | stable | 0.054 |
| `native_mem_max_bytes` | 6 | 28.670 | 0.021 | 0.07% | 28.633..28.696 | stable | 28.652 |
| `native_mem_max_bytes.calltrace` | 6 | 6.411 | 0.016 | 0.26% | 6.384..6.432 | stable | 6.401 |
| `native_mem_max_bytes.dictionary` | 6 | 6.803 | 0.000 | 0.00% | 6.803..6.803 | stable | 6.803 |
| `native_mem_max_bytes.jfr_buffers` | 6 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_max_bytes.line_tables` | 6 | 0.357 | 0.002 | 0.59% | 0.353..0.360 | stable | 0.356 |
| `native_mem_max_bytes.method_map` | 6 | 0.972 | 0.006 | 0.60% | 0.962..0.977 | stable | 0.964 |
| `native_mem_max_bytes.native_symbols` | 6 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_max_bytes.thread_filter` | 6 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_max_bytes.thread_info` | 6 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_max_bytes.thread_local` | 6 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_max_bytes.wallclock` | 6 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |
| `native_mem_max_observed_total_bytes` | 6 | 26.648 | 0.014 | 0.05% | 26.623..26.662 | stable | 26.642 |
| `native_mem_post_flush_live_bytes.calltrace` | 6 | 3.731 | 0.001 | 0.02% | 3.729..3.731 | stable | 3.730 |
| `native_mem_post_flush_live_bytes.dictionary` | 6 | 6.053 | 0.000 | 0.00% | 6.053..6.053 | stable | 6.053 |
| `native_mem_post_flush_live_bytes.jfr_buffers` | 6 | 1.158 | 0.000 | 0.00% | 1.158..1.158 | stable | 1.158 |
| `native_mem_post_flush_live_bytes.line_tables` | 6 | 0.357 | 0.002 | 0.59% | 0.353..0.360 | stable | 0.356 |
| `native_mem_post_flush_live_bytes.method_map` | 6 | 0.972 | 0.006 | 0.60% | 0.962..0.977 | stable | 0.964 |
| `native_mem_post_flush_live_bytes.native_symbols` | 6 | 12.867 | 0.000 | 0.00% | 12.867..12.867 | stable | 12.867 |
| `native_mem_post_flush_live_bytes.thread_filter` | 6 | 0.039 | 0.000 | 0.00% | 0.039..0.039 | stable | 0.039 |
| `native_mem_post_flush_live_bytes.thread_info` | 6 | 0.002 | 0.000 | 0.00% | 0.002..0.002 | stable | 0.002 |
| `native_mem_post_flush_live_bytes.thread_local` | 6 | 0.054 | 0.000 | 0.00% | 0.054..0.054 | stable | 0.054 |
| `native_mem_post_flush_live_bytes.wallclock` | 6 | 0.008 | 0.000 | 0.00% | 0.008..0.008 | stable | 0.008 |

### NMT committed (nmt arm) vs no-profiler control

| category | n | mean | SD | CV | class | noprof mean | profiler delta |
|---|---|---|---|---|---|---|---|
| class | 6 | 68.397 | 0.001 | 0.00% | stable | 65.458 | 2.939 |
| internal | 6 | 6.549 | 0.006 | 0.09% | stable | 3.319 | 3.230 |
| thread | 6 | 0.903 | 0.003 | 0.33% | stable | 0.900 | 0.003 |
| symbol | 6 | 5.878 | 0.000 | 0.00% | stable | 5.857 | 0.021 |
| code | 6 | 58.193 | 1.019 | 1.75% | banded | 53.608 | 4.585 |
| metaspace | 6 | 115.572 | 0.642 | 0.56% | stable | 115.686 | -0.114 |
| arena_chunk | 6 | 0.601 | 0.152 | 25.30% | noisy | 0.638 | -0.038 |
| native_memory_tracking | 6 | 10.751 | 0.028 | 0.26% | stable | 8.715 | 2.035 |
| total | 6 | 845.918 | 1.080 | 0.13% | stable | 833.073 | 12.844 |

### RSS at the sample point

| arm | metric | n | mean | SD |
|---|---|---|---|---|
| counters | VmRSS | 6 | 866.898 | 2.841 |
| counters | RssAnon | 6 | 840.193 | 2.840 |
| nmt | VmRSS | 6 | 877.973 | 2.653 |
| nmt | RssAnon | 6 | 851.270 | 2.629 |
| noprof | VmRSS | 3 | 835.350 | 2.962 |
| noprof | RssAnon | 3 | 812.786 | 2.881 |
