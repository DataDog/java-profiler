---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 31-52 cores)</summary>

```
1790604728 52
1790604733 52
1790604738 31
1790604743 31
1790604748 31
1790604753 31
1790604758 31
1790604763 31
1790604768 31
1790604773 31
1790604778 31
1790604783 31
1790604788 31
1790604793 31
1790604798 31
1790604803 31
1790604808 31
1790604813 31
1790604818 31
1790604823 31
```
</details>

---

