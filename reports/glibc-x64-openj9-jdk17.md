---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 12:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1793291795 29
1793291800 29
1793291805 29
1793291810 32
1793291815 32
1793291820 32
1793291825 32
1793291830 32
1793291835 32
1793291840 32
1793291845 32
1793291850 32
1793291855 32
1793291860 32
1793291865 32
1793291870 32
1793291875 32
1793291880 32
1793291885 32
1793291890 32
```
</details>

---

