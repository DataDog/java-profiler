---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 06:47:21 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 83-91 cores)</summary>

```
1794310989 91
1794310994 91
1794310999 91
1794311004 91
1794311009 91
1794311014 91
1794311019 91
1794311024 91
1794311029 91
1794311034 91
1794311039 91
1794311044 91
1794311049 85
1794311054 85
1794311059 85
1794311064 85
1794311069 85
1794311074 85
1794311079 85
1794311084 85
```
</details>

---

