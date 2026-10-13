---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-13 07:44:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791891549 48
1791891554 48
1791891559 48
1791891564 48
1791891569 48
1791891574 43
1791891579 43
1791891584 43
1791891589 43
1791891594 43
1791891599 43
1791891604 43
1791891609 43
1791891614 43
1791891619 43
1791891624 43
1791891629 43
1791891634 48
1791891639 48
1791891644 48
```
</details>

---

