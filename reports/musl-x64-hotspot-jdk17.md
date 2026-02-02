---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-02 12:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 12 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 71-94 cores)</summary>

```
1770051353 71
1770051358 71
1770051363 75
1770051368 75
1770051373 75
1770051378 75
1770051383 75
1770051388 75
1770051393 89
1770051398 89
1770051403 89
1770051408 89
1770051413 89
1770051418 89
1770051423 89
1770051428 89
1770051433 89
1770051438 89
1770051443 89
1770051448 89
```
</details>

---

