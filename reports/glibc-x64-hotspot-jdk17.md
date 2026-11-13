---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:36:49 EST

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
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1794569532 17
1794569537 17
1794569542 17
1794569547 17
1794569552 17
1794569557 15
1794569562 15
1794569567 15
1794569572 15
1794569577 15
1794569582 15
1794569587 15
1794569592 15
1794569597 17
1794569602 17
1794569607 17
1794569612 17
1794569617 17
1794569622 17
1794569627 17
```
</details>

---

