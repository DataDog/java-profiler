---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:58:45 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (7 unique values: 48-59 cores)</summary>

```
1778165574 52
1778165579 52
1778165584 52
1778165589 52
1778165594 54
1778165599 54
1778165604 48
1778165609 48
1778165614 52
1778165619 52
1778165624 52
1778165630 53
1778165635 53
1778165640 55
1778165645 55
1778165650 55
1778165655 55
1778165660 59
1778165665 59
1778165670 50
```
</details>

---

