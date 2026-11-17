---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:30:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
| Allocations | 210 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1794943493 25
1794943498 25
1794943503 25
1794943508 25
1794943513 25
1794943518 25
1794943523 25
1794943528 25
1794943533 25
1794943538 25
1794943543 25
1794943548 25
1794943553 25
1794943558 25
1794943563 25
1794943568 25
1794943573 25
1794943578 38
1794943583 38
1794943588 38
```
</details>

---

