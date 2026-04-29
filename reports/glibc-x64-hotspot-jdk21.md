---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 07:38:31 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1777462498 39
1777462503 39
1777462508 39
1777462513 39
1777462518 39
1777462523 44
1777462528 44
1777462533 44
1777462538 44
1777462543 44
1777462548 44
1777462553 44
1777462558 44
1777462563 44
1777462568 44
1777462573 44
1777462578 44
1777462583 44
1777462588 44
1777462593 44
```
</details>

---

