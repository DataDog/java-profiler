---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:41:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 444 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 75-94 cores)</summary>

```
1778171836 94
1778171841 94
1778171846 94
1778171851 94
1778171856 94
1778171861 94
1778171866 94
1778171871 94
1778171876 75
1778171881 75
1778171886 75
1778171891 75
1778171896 75
1778171901 75
1778171906 75
1778171911 77
1778171916 77
1778171921 77
1778171926 77
1778171931 77
```
</details>

---

