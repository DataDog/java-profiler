---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 13 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1789680045 23
1789680050 23
1789680055 23
1789680060 23
1789680065 23
1789680070 23
1789680075 23
1789680080 23
1789680085 23
1789680090 23
1789680095 23
1789680100 23
1789680105 23
1789680110 23
1789680115 23
1789680120 23
1789680125 23
1789680130 23
1789680135 28
1789680140 28
```
</details>

---

