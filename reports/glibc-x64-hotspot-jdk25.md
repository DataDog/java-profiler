---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 16:31:11 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 62 |
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
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 61-66 cores)</summary>

```
1793305618 61
1793305623 64
1793305628 64
1793305633 64
1793305638 64
1793305643 64
1793305648 64
1793305653 64
1793305658 66
1793305663 66
1793305668 64
1793305673 64
1793305678 64
1793305683 64
1793305688 64
1793305693 64
1793305698 64
1793305703 64
1793305708 64
1793305713 64
```
</details>

---

