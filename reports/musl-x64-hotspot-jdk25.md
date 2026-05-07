---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 17:34:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1778189509 90
1778189514 87
1778189519 87
1778189524 91
1778189529 91
1778189534 91
1778189539 91
1778189544 91
1778189549 91
1778189554 91
1778189559 91
1778189564 91
1778189569 91
1778189574 91
1778189579 91
1778189584 91
1778189589 91
1778189594 91
1778189599 91
1778189604 91
```
</details>

---

