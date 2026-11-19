---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:10:53 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (6 unique values: 51-68 cores)</summary>

```
1795129596 61
1795129601 51
1795129606 51
1795129611 51
1795129616 51
1795129621 51
1795129626 51
1795129631 53
1795129636 53
1795129641 53
1795129646 53
1795129651 53
1795129656 53
1795129661 53
1795129666 63
1795129671 63
1795129676 68
1795129681 68
1795129686 68
1795129691 68
```
</details>

---

