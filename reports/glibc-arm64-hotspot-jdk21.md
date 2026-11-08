---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794165885 24
1794165890 24
1794165895 24
1794165900 24
1794165905 24
1794165910 24
1794165915 29
1794165920 29
1794165925 34
1794165930 34
1794165935 34
1794165940 34
1794165945 34
1794165950 34
1794165955 34
1794165960 34
1794165965 34
1794165970 34
1794165975 34
1794165980 34
```
</details>

---

