---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:59:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 16-46 cores)</summary>

```
1795794910 17
1795794915 17
1795794920 17
1795794925 17
1795794930 17
1795794935 17
1795794940 17
1795794945 17
1795794950 17
1795794955 46
1795794960 46
1795794965 16
1795794970 16
1795794975 16
1795794980 16
1795794985 17
1795794990 17
1795794995 17
1795795000 17
1795795005 17
```
</details>

---

