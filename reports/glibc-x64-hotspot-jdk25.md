---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:58:32 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 42-64 cores)</summary>

```
1793789593 64
1793789598 64
1793789603 64
1793789608 64
1793789613 64
1793789618 64
1793789623 64
1793789628 64
1793789633 64
1793789638 64
1793789643 64
1793789648 64
1793789653 42
1793789658 42
1793789663 42
1793789668 42
1793789673 42
1793789678 42
1793789683 42
1793789688 42
```
</details>

---

