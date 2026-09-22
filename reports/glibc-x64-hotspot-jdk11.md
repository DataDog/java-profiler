---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:32:53 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 54-62 cores)</summary>

```
1790093834 62
1790093839 62
1790093844 62
1790093849 62
1790093854 62
1790093859 62
1790093864 62
1790093869 62
1790093874 62
1790093879 62
1790093884 62
1790093889 62
1790093894 62
1790093899 54
1790093904 54
1790093909 54
1790093914 54
1790093919 54
1790093924 54
1790093929 54
```
</details>

---

