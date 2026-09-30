---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1790785529 16
1790785534 16
1790785539 16
1790785544 16
1790785549 16
1790785554 16
1790785559 16
1790785564 16
1790785569 16
1790785574 16
1790785579 16
1790785584 16
1790785589 16
1790785594 16
1790785599 16
1790785604 16
1790785609 16
1790785614 16
1790785619 16
1790785624 16
```
</details>

---

