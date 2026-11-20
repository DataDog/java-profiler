---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:14:03 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795169396 36
1795169401 36
1795169406 36
1795169411 36
1795169416 36
1795169421 36
1795169426 36
1795169431 36
1795169436 36
1795169442 36
1795169447 36
1795169452 36
1795169457 36
1795169462 36
1795169467 31
1795169472 31
1795169477 31
1795169482 31
1795169487 31
1795169492 31
```
</details>

---

