---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:52:00 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 67-75 cores)</summary>

```
1789731979 67
1789731984 67
1789731989 75
1789731994 75
1789731999 75
1789732004 75
1789732009 75
1789732014 75
1789732019 75
1789732024 75
1789732029 73
1789732034 73
1789732039 73
1789732044 73
1789732049 73
1789732054 73
1789732060 73
1789732065 73
1789732070 73
1789732075 73
```
</details>

---

