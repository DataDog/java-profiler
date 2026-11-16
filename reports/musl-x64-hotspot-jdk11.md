---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:18:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1794823895 54
1794823900 54
1794823905 54
1794823910 54
1794823915 54
1794823920 54
1794823925 54
1794823930 54
1794823935 54
1794823940 54
1794823945 56
1794823950 56
1794823955 56
1794823960 56
1794823965 56
1794823970 56
1794823975 56
1794823980 56
1794823985 56
1794823990 56
```
</details>

---

