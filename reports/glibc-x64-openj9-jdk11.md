---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 13:03:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1794851939 54
1794851944 54
1794851949 54
1794851954 54
1794851959 54
1794851964 54
1794851969 54
1794851974 54
1794851979 54
1794851984 54
1794851989 54
1794851994 54
1794851999 54
1794852004 54
1794852009 54
1794852014 52
1794852019 52
1794852024 52
1794852029 52
1794852034 52
```
</details>

---

