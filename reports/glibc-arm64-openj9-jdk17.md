---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-23 05:47:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 27-34 cores)</summary>

```
1787478218 34
1787478223 34
1787478228 34
1787478233 34
1787478238 34
1787478243 34
1787478248 34
1787478253 34
1787478258 34
1787478263 34
1787478268 34
1787478273 34
1787478278 34
1787478283 34
1787478288 32
1787478293 32
1787478298 32
1787478303 32
1787478308 32
1787478313 32
```
</details>

---

