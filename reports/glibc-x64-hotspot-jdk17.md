---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (5 unique values: 17-32 cores)</summary>

```
1790785534 17
1790785539 17
1790785544 17
1790785549 17
1790785554 17
1790785559 17
1790785564 17
1790785569 19
1790785574 19
1790785579 19
1790785584 19
1790785589 19
1790785594 19
1790785599 19
1790785604 19
1790785609 27
1790785614 27
1790785619 27
1790785624 32
1790785629 32
```
</details>

---

