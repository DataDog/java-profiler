---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1770140754 32
1770140759 32
1770140764 32
1770140769 32
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
```
</details>

---

