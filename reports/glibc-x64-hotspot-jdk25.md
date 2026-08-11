---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 05:49:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1786441469 46
1786441474 46
1786441479 46
1786441484 46
1786441489 46
1786441494 46
1786441499 46
1786441504 46
1786441509 46
1786441514 46
1786441519 46
1786441524 46
1786441529 41
1786441534 41
1786441539 41
1786441544 41
1786441549 41
1786441554 41
1786441559 41
1786441564 41
```
</details>

---

