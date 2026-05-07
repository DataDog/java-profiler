---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:49:54 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 87-92 cores)</summary>

```
1778150773 92
1778150778 92
1778150783 92
1778150788 92
1778150793 92
1778150798 92
1778150803 92
1778150808 92
1778150813 92
1778150818 92
1778150823 92
1778150828 92
1778150833 90
1778150838 90
1778150843 90
1778150848 90
1778150853 90
1778150858 90
1778150863 90
1778150868 87
```
</details>

---

