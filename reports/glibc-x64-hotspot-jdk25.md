---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:07:35 EDT

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
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 64-71 cores)</summary>

```
1793372583 64
1793372588 64
1793372593 68
1793372598 68
1793372603 70
1793372608 70
1793372613 70
1793372618 70
1793372623 70
1793372628 70
1793372633 70
1793372638 70
1793372643 70
1793372648 71
1793372653 71
1793372658 71
1793372663 71
1793372668 71
1793372673 71
1793372678 71
```
</details>

---

