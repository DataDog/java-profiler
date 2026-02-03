---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 910 |
| Sample Rate | 15.17/sec |
| Health Score | 948% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (5 unique values: 35-59 cores)</summary>

```
1770124556 35
1770124561 35
1770124566 35
1770124571 37
1770124576 37
1770124581 37
1770124586 37
1770124591 37
1770124596 37
1770124601 36
1770124606 36
1770124611 37
1770124616 37
1770124621 37
1770124626 37
1770124631 37
1770124636 37
1770124641 37
1770124646 37
1770124651 37
```
</details>

---

