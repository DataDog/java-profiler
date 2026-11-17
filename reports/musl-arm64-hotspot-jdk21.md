---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 05:59:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 19-44 cores)</summary>

```
1794912834 19
1794912839 19
1794912844 19
1794912849 19
1794912854 19
1794912859 19
1794912864 19
1794912869 32
1794912874 32
1794912879 32
1794912884 32
1794912889 32
1794912894 32
1794912899 32
1794912904 32
1794912909 32
1794912915 32
1794912920 32
1794912925 44
1794912930 44
```
</details>

---

