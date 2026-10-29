---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 16:31:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1793305603 78
1793305608 78
1793305613 78
1793305618 78
1793305623 78
1793305628 80
1793305633 80
1793305638 80
1793305643 80
1793305648 80
1793305653 80
1793305658 80
1793305663 80
1793305668 80
1793305673 80
1793305678 80
1793305683 80
1793305688 80
1793305693 80
1793305698 80
```
</details>

---

