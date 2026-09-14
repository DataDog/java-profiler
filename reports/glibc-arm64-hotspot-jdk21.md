---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-14 12:04:46 EDT

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1789401543 48
1789401548 48
1789401553 48
1789401558 48
1789401563 48
1789401568 48
1789401573 48
1789401578 48
1789401583 48
1789401588 48
1789401593 48
1789401598 48
1789401603 48
1789401608 48
1789401613 48
1789401618 48
1789401623 48
1789401628 48
1789401633 46
1789401638 46
```
</details>

---

