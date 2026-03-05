---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 26-30 cores)</summary>

```
1772734995 26
1772735000 26
1772735005 26
1772735010 26
1772735015 26
1772735020 26
1772735025 26
1772735030 26
1772735035 30
1772735040 30
1772735045 30
1772735050 30
1772735055 27
1772735060 27
1772735065 27
1772735070 27
1772735075 29
1772735080 29
1772735085 29
1772735090 29
```
</details>

---

