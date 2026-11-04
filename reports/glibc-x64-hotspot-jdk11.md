---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:58:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793789583 32
1793789588 32
1793789593 32
1793789598 32
1793789603 32
1793789608 32
1793789613 32
1793789618 32
1793789623 32
1793789628 32
1793789633 32
1793789638 32
1793789643 32
1793789648 32
1793789653 32
1793789658 32
1793789663 32
1793789668 32
1793789673 32
1793789678 32
```
</details>

---

