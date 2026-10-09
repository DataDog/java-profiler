---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 07:59:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (5 unique values: 36-44 cores)</summary>

```
1791546657 44
1791546662 44
1791546667 44
1791546672 44
1791546677 44
1791546682 44
1791546687 44
1791546692 44
1791546697 44
1791546702 44
1791546707 44
1791546712 44
1791546717 44
1791546722 44
1791546727 43
1791546733 43
1791546738 43
1791546743 43
1791546748 41
1791546753 41
```
</details>

---

