---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 13:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794939919 38
1794939924 38
1794939929 38
1794939934 38
1794939939 38
1794939944 38
1794939949 38
1794939954 38
1794939959 38
1794939964 38
1794939969 38
1794939974 51
1794939979 51
1794939984 51
1794939989 51
1794939994 51
1794939999 51
1794940004 51
1794940009 51
1794940014 51
```
</details>

---

