---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-28 11:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 35-43 cores)</summary>

```
1779981608 35
1779981613 35
1779981618 35
1779981623 35
1779981628 35
1779981633 35
1779981638 43
1779981643 43
1779981648 39
1779981653 39
1779981658 39
1779981663 39
1779981668 39
1779981673 39
1779981679 39
1779981684 39
1779981689 39
1779981694 39
1779981699 41
1779981704 41
```
</details>

---

