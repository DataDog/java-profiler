---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 19:07:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793836918 32
1793836923 32
1793836928 32
1793836933 32
1793836938 32
1793836943 32
1793836948 32
1793836953 32
1793836958 32
1793836963 32
1793836968 32
1793836973 32
1793836978 32
1793836983 32
1793836988 32
1793836993 32
1793836998 32
1793837003 32
1793837008 32
1793837013 32
```
</details>

---

