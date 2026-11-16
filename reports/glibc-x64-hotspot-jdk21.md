---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 12:06:59 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (3 unique values: 82-85 cores)</summary>

```
1794848458 82
1794848463 82
1794848468 83
1794848473 83
1794848478 85
1794848483 85
1794848488 85
1794848493 85
1794848498 85
1794848503 85
1794848508 85
1794848513 85
1794848518 85
1794848523 83
1794848528 83
1794848533 83
1794848538 83
1794848543 83
1794848548 83
1794848553 83
```
</details>

---

