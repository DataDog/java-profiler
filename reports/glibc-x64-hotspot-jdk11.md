---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 02:56:27 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 63-66 cores)</summary>

```
1778568779 66
1778568784 66
1778568789 63
1778568794 63
1778568799 63
1778568804 63
1778568809 63
1778568814 63
1778568819 63
1778568824 63
1778568829 63
1778568834 63
1778568839 63
1778568844 63
1778568849 63
1778568854 63
1778568859 63
1778568864 63
1778568869 63
1778568874 63
```
</details>

---

