---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1788151583 74
1788151588 74
1788151593 94
1788151598 94
1788151603 94
1788151608 94
1788151613 94
1788151618 94
1788151623 96
1788151628 96
1788151633 96
1788151638 96
1788151643 96
1788151648 96
1788151653 96
1788151658 96
1788151663 96
1788151668 96
1788151673 96
1788151678 96
```
</details>

---

