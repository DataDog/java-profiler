---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 11:36:51 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1790782308 13
1790782313 15
1790782318 15
1790782323 15
1790782328 15
1790782333 15
1790782338 15
1790782343 15
1790782348 15
1790782353 15
1790782358 15
1790782363 15
1790782368 15
1790782373 15
1790782378 15
1790782383 15
1790782388 15
1790782393 15
1790782398 15
1790782403 15
```
</details>

---

