---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 09:07:16 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793800922 40
1793800927 40
1793800932 40
1793800937 40
1793800942 40
1793800947 40
1793800952 40
1793800957 40
1793800962 40
1793800967 40
1793800972 40
1793800977 40
1793800982 40
1793800987 40
1793800992 40
1793800997 40
1793801002 40
1793801007 40
1793801012 40
1793801017 40
```
</details>

---

