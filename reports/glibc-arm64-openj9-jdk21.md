---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-19 05:47:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 33-43 cores)</summary>

```
1789811058 43
1789811063 41
1789811068 41
1789811073 41
1789811078 41
1789811083 41
1789811088 41
1789811093 41
1789811098 41
1789811103 41
1789811108 41
1789811113 41
1789811118 41
1789811123 41
1789811128 43
1789811133 43
1789811138 43
1789811143 43
1789811148 38
1789811153 38
```
</details>

---

