---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-26 01:03:07 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 13 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 14-19 cores)</summary>

```
1790398427 14
1790398432 14
1790398437 14
1790398442 14
1790398447 14
1790398452 14
1790398457 19
1790398462 19
1790398467 14
1790398472 14
1790398477 14
1790398482 14
1790398487 14
1790398492 14
1790398497 14
1790398502 14
1790398507 14
1790398512 14
1790398517 19
1790398522 19
```
</details>

---

