---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
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
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 9-29 cores)</summary>

```
1791193589 9
1791193594 9
1791193599 9
1791193604 9
1791193609 9
1791193614 9
1791193619 9
1791193624 29
1791193629 29
1791193634 27
1791193639 27
1791193644 27
1791193649 27
1791193654 27
1791193659 27
1791193664 27
1791193669 27
1791193674 27
1791193679 27
1791193684 29
```
</details>

---

