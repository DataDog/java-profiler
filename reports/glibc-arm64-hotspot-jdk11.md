---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 12:30:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1790785534 28
1790785539 28
1790785544 28
1790785549 28
1790785554 28
1790785559 28
1790785564 28
1790785569 28
1790785574 28
1790785579 28
1790785584 28
1790785589 28
1790785594 28
1790785599 28
1790785605 28
1790785610 28
1790785615 28
1790785620 28
1790785625 28
1790785630 28
```
</details>

---

