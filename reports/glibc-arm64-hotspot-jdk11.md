---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:01 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795449513 48
1795449518 48
1795449523 64
1795449528 64
1795449533 48
1795449539 48
1795449544 48
1795449549 48
1795449554 48
1795449559 48
1795449564 48
1795449569 48
1795449574 48
1795449579 48
1795449584 48
1795449589 48
1795449594 48
1795449599 48
1795449604 48
1795449609 48
```
</details>

---

