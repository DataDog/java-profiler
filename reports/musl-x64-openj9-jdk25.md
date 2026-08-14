---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-14 01:01:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1786683289 48
1786683294 48
1786683299 48
1786683304 42
1786683309 42
1786683314 42
1786683319 42
1786683324 42
1786683329 42
1786683334 42
1786683339 42
1786683344 42
1786683349 42
1786683354 42
1786683359 42
1786683364 42
1786683369 42
1786683374 42
1786683379 42
1786683384 42
```
</details>

---

