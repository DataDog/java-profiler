---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 09:07:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 39-48 cores)</summary>

```
1793800937 47
1793800942 48
1793800947 48
1793800952 48
1793800957 48
1793800962 48
1793800967 48
1793800972 48
1793800977 48
1793800982 48
1793800987 48
1793800992 48
1793800997 48
1793801002 48
1793801007 48
1793801012 48
1793801017 48
1793801022 48
1793801027 48
1793801032 43
```
</details>

---

