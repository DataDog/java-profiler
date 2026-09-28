---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 03:36:30 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 12-56 cores)</summary>

```
1790580743 16
1790580748 16
1790580753 16
1790580758 16
1790580763 16
1790580768 16
1790580773 16
1790580778 16
1790580783 12
1790580788 12
1790580793 12
1790580798 12
1790580803 12
1790580808 12
1790580813 14
1790580818 14
1790580823 36
1790580828 36
1790580833 36
1790580838 36
```
</details>

---

