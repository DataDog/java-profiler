---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 09:21:52 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787059038 43
1787059043 43
1787059048 43
1787059054 43
1787059059 43
1787059064 43
1787059069 48
1787059074 48
1787059079 48
1787059084 48
1787059089 48
1787059094 48
1787059099 48
1787059104 48
1787059109 48
1787059114 48
1787059119 48
1787059124 48
1787059129 48
1787059134 48
```
</details>

---

