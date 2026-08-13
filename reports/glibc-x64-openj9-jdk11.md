---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 06:34:59 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786617059 30
1786617064 30
1786617069 30
1786617074 30
1786617079 30
1786617084 30
1786617089 30
1786617094 30
1786617099 30
1786617104 32
1786617109 32
1786617114 32
1786617119 32
1786617124 32
1786617129 32
1786617134 32
1786617139 32
1786617144 32
1786617149 32
1786617154 32
```
</details>

---

