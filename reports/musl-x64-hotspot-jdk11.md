---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:38:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1791541839 85
1791541844 85
1791541849 85
1791541854 85
1791541859 85
1791541864 85
1791541869 85
1791541874 85
1791541879 85
1791541884 85
1791541889 85
1791541894 85
1791541899 85
1791541904 85
1791541909 85
1791541914 85
1791541919 85
1791541924 85
1791541929 85
1791541934 83
```
</details>

---

