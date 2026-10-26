---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 09:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 10 |
| Allocations | 566 |

<details>
<summary>CPU Timeline (4 unique values: 53-76 cores)</summary>

```
1793021594 57
1793021599 57
1793021604 57
1793021609 76
1793021614 76
1793021619 76
1793021624 76
1793021629 76
1793021634 55
1793021639 55
1793021644 55
1793021650 55
1793021655 55
1793021660 55
1793021665 55
1793021670 55
1793021675 55
1793021680 55
1793021685 55
1793021690 55
```
</details>

---

