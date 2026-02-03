---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1770140774 32
1770140779 32
1770140784 32
1770140789 32
1770140794 32
1770140799 32
1770140804 32
1770140809 32
1770140814 32
1770140819 32
1770140824 32
1770140829 32
1770140834 32
1770140839 32
1770140844 32
1770140849 32
1770140854 32
1770140859 32
1770140864 32
1770140869 32
```
</details>

---

