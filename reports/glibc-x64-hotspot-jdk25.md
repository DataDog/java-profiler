---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 10:47:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 78-83 cores)</summary>

```
1791988868 81
1791988873 81
1791988878 81
1791988883 81
1791988888 81
1791988893 83
1791988898 83
1791988903 78
1791988908 78
1791988913 78
1791988918 78
1791988923 78
1791988929 78
1791988934 78
1791988939 78
1791988944 78
1791988949 78
1791988954 78
1791988959 78
1791988964 78
```
</details>

---

