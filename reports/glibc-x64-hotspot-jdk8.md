---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 79-87 cores)</summary>

```
1794495884 82
1794495889 83
1794495894 83
1794495899 83
1794495904 85
1794495909 85
1794495914 85
1794495919 87
1794495924 87
1794495929 87
1794495934 87
1794495939 87
1794495944 87
1794495949 87
1794495954 87
1794495959 87
1794495964 79
1794495969 79
1794495974 79
1794495979 79
```
</details>

---

