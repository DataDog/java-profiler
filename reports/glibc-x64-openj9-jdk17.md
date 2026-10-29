---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 09:55:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 13-15 cores)</summary>

```
1793281790 15
1793281795 15
1793281800 15
1793281805 15
1793281810 15
1793281815 15
1793281820 15
1793281825 15
1793281830 15
1793281835 15
1793281840 15
1793281845 15
1793281850 13
1793281855 13
1793281860 13
1793281865 13
1793281870 13
1793281875 13
1793281880 13
1793281885 13
```
</details>

---

