---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:18:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 9 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1786972379 43
1786972384 43
1786972389 43
1786972394 42
1786972399 42
1786972404 42
1786972409 42
1786972414 42
1786972419 42
1786972424 42
1786972429 42
1786972434 42
1786972439 42
1786972444 43
1786972449 43
1786972454 43
1786972459 43
1786972464 43
1786972469 43
1786972474 43
```
</details>

---

