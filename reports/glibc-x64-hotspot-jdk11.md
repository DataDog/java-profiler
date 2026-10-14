---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 10:47:47 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1791988863 54
1791988868 54
1791988873 54
1791988878 54
1791988883 54
1791988888 56
1791988893 56
1791988898 56
1791988903 56
1791988908 56
1791988913 56
1791988918 56
1791988923 56
1791988928 56
1791988933 56
1791988938 56
1791988943 56
1791988948 56
1791988953 56
1791988958 56
```
</details>

---

