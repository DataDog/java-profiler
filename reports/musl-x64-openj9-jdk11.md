---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 12:40:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 52-57 cores)</summary>

```
1791995648 55
1791995653 55
1791995658 55
1791995663 55
1791995668 55
1791995673 55
1791995678 55
1791995683 57
1791995688 57
1791995693 52
1791995698 52
1791995703 52
1791995708 52
1791995713 52
1791995718 52
1791995723 52
1791995728 52
1791995733 52
1791995738 52
1791995743 52
```
</details>

---

