---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 938 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778582453 62
1778582458 62
1778582463 62
1778582468 62
1778582473 62
1778582478 62
1778582483 62
1778582488 62
1778582493 64
1778582498 64
1778582503 64
1778582508 64
1778582513 64
1778582518 64
1778582523 64
1778582528 64
1778582533 64
1778582538 64
1778582543 64
1778582548 64
```
</details>

---

