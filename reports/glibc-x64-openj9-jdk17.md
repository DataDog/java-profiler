---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-05 20:41:45 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 13-32 cores)</summary>

```
1770341800 13
1770341805 13
1770341810 13
1770341815 13
1770341820 13
1770341825 13
1770341830 13
1770341835 13
1770341840 13
1770341845 13
1770341850 13
1770341855 13
1770341860 13
1770341865 13
1770341870 13
1770341875 13
1770341880 13
1770341885 13
1770341890 32
1770341895 32
```
</details>

---

