---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 00:57:14 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1786596773 32
1786596778 32
1786596783 32
1786596788 32
1786596793 32
1786596798 32
1786596803 32
1786596808 32
1786596813 32
1786596818 32
1786596823 32
1786596828 32
1786596833 32
1786596838 32
1786596843 32
1786596848 32
1786596853 32
1786596858 32
1786596863 32
1786596868 32
```
</details>

---

