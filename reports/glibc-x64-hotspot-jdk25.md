---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:53:34 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 71-73 cores)</summary>

```
1778172506 73
1778172511 73
1778172516 73
1778172521 72
1778172526 72
1778172531 72
1778172536 72
1778172541 72
1778172546 72
1778172551 72
1778172556 73
1778172561 73
1778172566 71
1778172571 71
1778172576 71
1778172581 71
1778172586 71
1778172591 71
1778172596 71
1778172601 71
```
</details>

---

