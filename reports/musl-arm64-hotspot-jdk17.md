---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 10:05:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1778507974 64
1778507979 64
1778507984 64
1778507989 64
1778507994 64
1778507999 64
1778508004 64
1778508009 64
1778508014 64
1778508019 64
1778508024 64
1778508029 64
1778508034 64
1778508039 64
1778508044 64
1778508049 64
1778508054 64
1778508059 64
1778508064 64
1778508069 64
```
</details>

---

