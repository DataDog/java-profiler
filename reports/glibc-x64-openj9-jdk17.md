---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 14:59:47 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 50-75 cores)</summary>

```
1776279183 75
1776279188 75
1776279193 75
1776279198 75
1776279203 55
1776279208 55
1776279213 55
1776279218 50
1776279223 50
1776279228 53
1776279233 53
1776279238 53
1776279243 53
1776279248 53
1776279253 53
1776279258 53
1776279263 50
1776279268 50
1776279273 50
1776279278 50
```
</details>

---

