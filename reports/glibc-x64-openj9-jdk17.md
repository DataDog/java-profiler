---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:19:16 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 83-91 cores)</summary>

```
1794582892 83
1794582897 83
1794582902 91
1794582907 91
1794582912 91
1794582917 91
1794582922 91
1794582927 91
1794582932 91
1794582937 91
1794582942 91
1794582947 91
1794582952 91
1794582957 91
1794582962 91
1794582967 91
1794582972 91
1794582977 91
1794582982 91
1794582987 91
```
</details>

---

