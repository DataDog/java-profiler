---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:26:29 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1789982421 18
1789982426 18
1789982431 18
1789982436 18
1789982441 18
1789982446 18
1789982451 18
1789982456 18
1789982461 18
1789982466 18
1789982471 18
1789982476 20
1789982481 20
1789982486 20
1789982491 20
1789982496 20
1789982501 20
1789982506 20
1789982511 20
1789982516 20
```
</details>

---

