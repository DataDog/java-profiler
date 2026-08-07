---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 16:14:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (6 unique values: 46-57 cores)</summary>

```
1786133461 55
1786133466 55
1786133471 55
1786133476 55
1786133481 55
1786133486 55
1786133491 55
1786133496 57
1786133501 57
1786133506 57
1786133511 57
1786133516 57
1786133521 57
1786133526 57
1786133531 47
1786133536 47
1786133541 47
1786133546 47
1786133551 47
1786133556 47
```
</details>

---

