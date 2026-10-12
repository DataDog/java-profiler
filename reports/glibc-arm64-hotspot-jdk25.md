---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 33-44 cores)</summary>

```
1791794210 33
1791794215 33
1791794220 33
1791794225 33
1791794230 33
1791794235 33
1791794240 33
1791794245 33
1791794250 36
1791794255 36
1791794260 36
1791794265 36
1791794270 34
1791794275 34
1791794280 39
1791794285 39
1791794290 39
1791794295 39
1791794300 39
1791794305 39
```
</details>

---

