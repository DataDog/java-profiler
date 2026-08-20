---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 07:23:18 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787224723 43
1787224728 43
1787224733 43
1787224738 43
1787224743 43
1787224748 43
1787224753 43
1787224758 43
1787224763 43
1787224768 43
1787224773 43
1787224778 43
1787224783 43
1787224788 43
1787224793 43
1787224798 48
1787224803 48
1787224808 48
1787224813 48
1787224818 48
```
</details>

---

