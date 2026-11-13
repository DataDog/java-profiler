---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:10:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794586031 44
1794586036 44
1794586041 44
1794586046 48
1794586051 48
1794586056 48
1794586061 48
1794586066 48
1794586071 48
1794586076 48
1794586081 48
1794586086 48
1794586091 48
1794586096 48
1794586101 48
1794586106 48
1794586111 48
1794586116 48
1794586121 48
1794586126 48
```
</details>

---

