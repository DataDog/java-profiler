---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-08 05:50:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1786182264 28
1786182269 28
1786182274 28
1786182279 28
1786182284 28
1786182289 28
1786182294 28
1786182299 28
1786182304 28
1786182309 28
1786182314 28
1786182319 28
1786182324 28
1786182329 28
1786182334 28
1786182339 28
1786182344 28
1786182349 28
1786182354 28
1786182359 30
```
</details>

---

