---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 15:00:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 64-69 cores)</summary>

```
1786388103 66
1786388108 66
1786388113 66
1786388118 66
1786388123 66
1786388128 64
1786388133 64
1786388138 64
1786388143 64
1786388148 64
1786388153 67
1786388158 67
1786388163 67
1786388168 67
1786388173 67
1786388178 67
1786388183 69
1786388188 69
1786388193 69
1786388198 69
```
</details>

---

