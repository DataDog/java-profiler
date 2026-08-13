---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 00:57:14 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 50-63 cores)</summary>

```
1786596773 50
1786596778 50
1786596783 50
1786596788 63
1786596793 63
1786596798 63
1786596803 61
1786596808 61
1786596813 61
1786596819 61
1786596824 61
1786596829 61
1786596834 61
1786596839 61
1786596844 61
1786596849 61
1786596854 63
1786596859 63
1786596864 63
1786596869 63
```
</details>

---

