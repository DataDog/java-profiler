---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 06:34:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 56-59 cores)</summary>

```
1786617044 56
1786617049 56
1786617054 56
1786617059 56
1786617064 56
1786617069 56
1786617074 56
1786617079 56
1786617084 56
1786617089 56
1786617094 59
1786617099 59
1786617104 59
1786617109 59
1786617114 59
1786617119 59
1786617124 59
1786617129 59
1786617134 59
1786617139 59
```
</details>

---

