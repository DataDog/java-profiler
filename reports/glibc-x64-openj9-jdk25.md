---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:00:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 80-88 cores)</summary>

```
1793098464 88
1793098469 88
1793098474 88
1793098479 88
1793098484 88
1793098489 88
1793098494 88
1793098499 88
1793098504 88
1793098509 88
1793098514 88
1793098519 88
1793098524 88
1793098529 88
1793098534 88
1793098539 88
1793098544 88
1793098549 88
1793098554 88
1793098559 88
```
</details>

---

