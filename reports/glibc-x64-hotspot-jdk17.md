---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-05 20:41:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 55-78 cores)</summary>

```
1770341770 78
1770341775 78
1770341780 78
1770341785 78
1770341790 78
1770341795 56
1770341800 56
1770341805 56
1770341810 56
1770341815 56
1770341820 56
1770341825 56
1770341830 56
1770341835 56
1770341840 56
1770341845 55
1770341850 55
1770341855 55
1770341860 55
1770341865 55
```
</details>

---

