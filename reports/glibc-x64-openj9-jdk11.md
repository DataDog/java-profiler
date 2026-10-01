---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 09:06:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (5 unique values: 15-29 cores)</summary>

```
1790859745 15
1790859750 15
1790859755 15
1790859760 17
1790859765 17
1790859770 17
1790859775 17
1790859780 17
1790859785 17
1790859790 29
1790859795 29
1790859800 29
1790859805 29
1790859810 29
1790859815 29
1790859820 29
1790859825 29
1790859830 29
1790859835 29
1790859840 26
```
</details>

---

