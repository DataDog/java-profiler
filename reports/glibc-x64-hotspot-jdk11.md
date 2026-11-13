---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:47:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 87-93 cores)</summary>

```
1794580942 89
1794580947 89
1794580952 89
1794580957 89
1794580962 89
1794580967 89
1794580972 89
1794580977 87
1794580982 87
1794580987 87
1794580992 87
1794580997 87
1794581002 87
1794581007 87
1794581012 87
1794581017 87
1794581022 87
1794581027 87
1794581032 87
1794581037 87
```
</details>

---

