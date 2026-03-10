---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 44-58 cores)</summary>

```
1773165000 54
1773165005 54
1773165010 54
1773165015 54
1773165020 54
1773165025 54
1773165030 54
1773165035 54
1773165040 54
1773165045 54
1773165050 54
1773165055 54
1773165060 54
1773165065 54
1773165070 54
1773165075 58
1773165080 58
1773165085 58
1773165090 58
1773165095 54
```
</details>

---

