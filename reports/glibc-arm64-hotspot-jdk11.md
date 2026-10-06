---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:09 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 11 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1791289498 35
1791289504 35
1791289509 35
1791289514 35
1791289519 35
1791289524 35
1791289529 35
1791289534 48
1791289539 48
1791289544 48
1791289549 48
1791289554 48
1791289559 48
1791289564 37
1791289569 37
1791289574 37
1791289579 37
1791289584 37
1791289589 37
1791289594 37
```
</details>

---

