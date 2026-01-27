---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-27 09:51:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 16.63/sec |
| Health Score | 1039% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 23.57/sec |
| Health Score | 1473% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1769524870 32
1769524875 32
1769524880 32
1769524885 29
1769524890 29
1769524895 29
1769524900 29
1769524905 29
1769524910 29
1769524915 29
1769524920 29
1769524925 29
1769524930 29
1769524935 29
1769524940 29
1769524945 29
1769524950 29
1769524955 29
1769524960 29
1769524965 29
```
</details>

---

