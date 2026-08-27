---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787806336 29
1787806341 29
1787806346 34
1787806351 34
1787806356 34
1787806361 34
1787806366 34
1787806371 34
1787806376 34
1787806381 34
1787806386 34
1787806391 34
1787806396 34
1787806401 34
1787806406 34
1787806411 34
1787806416 34
1787806421 34
1787806426 34
1787806431 34
```
</details>

---

