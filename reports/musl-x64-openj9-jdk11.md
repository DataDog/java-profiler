---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:33:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 10 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1791980898 56
1791980903 56
1791980908 56
1791980913 56
1791980918 58
1791980923 58
1791980928 58
1791980933 58
1791980938 58
1791980943 58
1791980948 58
1791980953 58
1791980958 58
1791980963 58
1791980968 58
1791980974 58
1791980979 58
1791980984 58
1791980989 58
1791980994 58
```
</details>

---

