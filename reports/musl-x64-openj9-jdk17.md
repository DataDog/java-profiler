---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 11:23:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 61-84 cores)</summary>

```
1778512723 65
1778512728 65
1778512733 65
1778512738 61
1778512743 61
1778512748 81
1778512753 81
1778512758 81
1778512763 81
1778512768 81
1778512773 81
1778512778 81
1778512783 81
1778512788 81
1778512793 81
1778512798 81
1778512803 81
1778512808 81
1778512813 81
1778512818 84
```
</details>

---

