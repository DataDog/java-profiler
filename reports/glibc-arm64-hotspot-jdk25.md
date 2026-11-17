---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:58:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 10 |
| Allocations | 126 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 11 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 35-51 cores)</summary>

```
1794912884 51
1794912889 51
1794912894 51
1794912899 51
1794912905 51
1794912910 51
1794912915 51
1794912920 51
1794912925 51
1794912930 51
1794912935 51
1794912940 51
1794912945 51
1794912950 51
1794912955 51
1794912960 51
1794912965 51
1794912970 51
1794912975 51
1794912980 35
```
</details>

---

