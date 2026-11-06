---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 21:05:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 961 |
| Sample Rate | 16.02/sec |
| Health Score | 1001% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793930519 48
1793930524 48
1793930529 48
1793930534 48
1793930539 48
1793930544 48
1793930549 48
1793930554 48
1793930559 48
1793930564 48
1793930569 48
1793930574 48
1793930579 48
1793930584 48
1793930589 48
1793930594 48
1793930599 48
1793930604 48
1793930609 48
1793930614 48
```
</details>

---

