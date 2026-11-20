---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:15:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 64-69 cores)</summary>

```
1795194610 69
1795194615 69
1795194620 69
1795194625 69
1795194630 69
1795194635 69
1795194640 69
1795194645 69
1795194650 69
1795194655 69
1795194660 69
1795194665 69
1795194670 66
1795194675 66
1795194680 66
1795194685 64
1795194690 64
1795194695 64
1795194700 64
1795194705 64
```
</details>

---

