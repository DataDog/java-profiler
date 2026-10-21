---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 01:05:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 40-93 cores)</summary>

```
1792558754 89
1792558759 91
1792558764 91
1792558769 91
1792558774 91
1792558779 91
1792558784 93
1792558789 93
1792558794 93
1792558799 93
1792558804 93
1792558809 93
1792558814 93
1792558819 93
1792558824 93
1792558829 93
1792558834 93
1792558839 93
1792558844 93
1792558849 93
```
</details>

---

