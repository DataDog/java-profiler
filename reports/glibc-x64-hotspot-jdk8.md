---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 20-25 cores)</summary>

```
1772734995 20
1772735000 20
1772735005 20
1772735010 20
1772735015 25
1772735020 25
1772735025 25
1772735030 25
1772735035 23
1772735040 23
1772735045 25
1772735050 25
1772735055 22
1772735060 22
1772735065 22
1772735070 22
1772735075 22
1772735080 22
1772735085 22
1772735090 22
```
</details>

---

