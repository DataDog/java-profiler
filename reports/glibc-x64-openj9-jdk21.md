---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:28:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 33-63 cores)</summary>

```
1792373020 33
1792373025 33
1792373030 33
1792373035 33
1792373040 53
1792373045 53
1792373050 53
1792373055 53
1792373060 58
1792373065 58
1792373070 58
1792373075 58
1792373080 58
1792373085 58
1792373090 58
1792373095 63
1792373100 63
1792373105 63
1792373110 63
1792373115 63
```
</details>

---

