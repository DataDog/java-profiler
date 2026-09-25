---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 05:16:43 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1069 |
| Sample Rate | 17.82/sec |
| Health Score | 1114% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 51-57 cores)</summary>

```
1790327398 51
1790327403 53
1790327408 53
1790327413 55
1790327418 55
1790327423 55
1790327428 55
1790327433 55
1790327438 55
1790327443 55
1790327448 57
1790327453 57
1790327458 57
1790327463 57
1790327468 57
1790327473 57
1790327478 57
1790327483 57
1790327488 57
1790327493 57
```
</details>

---

