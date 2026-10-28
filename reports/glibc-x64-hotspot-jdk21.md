---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 10:29:09 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793197479 32
1793197484 30
1793197489 30
1793197494 30
1793197499 30
1793197504 30
1793197509 30
1793197514 30
1793197519 30
1793197524 30
1793197529 30
1793197534 30
1793197539 30
1793197544 30
1793197549 30
1793197554 30
1793197559 30
1793197564 30
1793197569 30
1793197574 30
```
</details>

---

