---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 19:51:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 28-78 cores)</summary>

```
1793404052 28
1793404057 28
1793404062 28
1793404067 28
1793404072 28
1793404078 28
1793404083 28
1793404088 28
1793404093 28
1793404098 28
1793404103 28
1793404108 28
1793404113 28
1793404118 45
1793404123 45
1793404128 45
1793404133 78
1793404138 78
1793404143 78
1793404148 78
```
</details>

---

