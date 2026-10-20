---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 14:20:48 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 85-90 cores)</summary>

```
1792520232 89
1792520237 89
1792520242 85
1792520247 85
1792520252 88
1792520257 88
1792520262 88
1792520267 88
1792520272 88
1792520277 88
1792520282 90
1792520287 90
1792520292 90
1792520297 90
1792520302 90
1792520307 90
1792520312 90
1792520317 90
1792520322 90
1792520327 90
```
</details>

---

