---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 11:34:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790177329 48
1790177334 48
1790177339 43
1790177344 43
1790177349 43
1790177354 43
1790177359 43
1790177364 43
1790177369 43
1790177374 43
1790177379 43
1790177384 43
1790177389 43
1790177395 48
1790177400 48
1790177405 48
1790177410 48
1790177415 48
1790177420 48
1790177425 48
```
</details>

---

