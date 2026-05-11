---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 66-69 cores)</summary>

```
1778512705 68
1778512710 68
1778512715 68
1778512720 66
1778512725 66
1778512730 66
1778512735 66
1778512740 66
1778512746 66
1778512751 66
1778512756 66
1778512761 68
1778512766 68
1778512771 68
1778512776 68
1778512781 68
1778512786 68
1778512791 68
1778512796 68
1778512801 69
```
</details>

---

