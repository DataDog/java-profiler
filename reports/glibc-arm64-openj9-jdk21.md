---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 06:34:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (4 unique values: 26-30 cores)</summary>

```
1786617034 26
1786617039 26
1786617044 26
1786617049 26
1786617054 26
1786617059 26
1786617064 26
1786617069 26
1786617074 28
1786617079 28
1786617084 28
1786617089 28
1786617094 28
1786617099 28
1786617104 28
1786617109 28
1786617114 30
1786617119 30
1786617124 30
1786617129 30
```
</details>

---

