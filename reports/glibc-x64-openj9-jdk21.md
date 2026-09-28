---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 15:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (2 unique values: 44-52 cores)</summary>

```
1790621860 52
1790621865 52
1790621870 52
1790621875 52
1790621880 52
1790621885 52
1790621890 52
1790621895 52
1790621900 52
1790621905 52
1790621910 52
1790621915 52
1790621920 44
1790621925 44
1790621930 44
1790621935 44
1790621940 44
1790621945 44
1790621950 44
1790621955 44
```
</details>

---

