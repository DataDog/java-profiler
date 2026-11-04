---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1793829504 59
1793829509 59
1793829514 59
1793829519 59
1793829524 55
1793829529 55
1793829534 55
1793829539 55
1793829544 55
1793829549 55
1793829554 55
1793829559 55
1793829564 57
1793829569 57
1793829574 57
1793829579 57
1793829584 57
1793829589 57
1793829594 59
1793829599 59
```
</details>

---

