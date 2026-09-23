---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 56-88 cores)</summary>

```
1790193509 66
1790193514 66
1790193519 66
1790193524 66
1790193529 88
1790193534 88
1790193539 56
1790193544 56
1790193549 56
1790193554 56
1790193559 56
1790193564 56
1790193569 56
1790193574 56
1790193579 56
1790193584 56
1790193589 56
1790193594 56
1790193599 56
1790193604 56
```
</details>

---

