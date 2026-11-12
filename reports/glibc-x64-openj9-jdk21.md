---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:01:28 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1794477281 30
1794477286 30
1794477291 30
1794477296 30
1794477301 30
1794477306 30
1794477311 30
1794477316 30
1794477321 30
1794477326 28
1794477331 28
1794477336 28
1794477341 28
1794477346 28
1794477351 28
1794477356 28
1794477361 28
1794477366 28
1794477371 28
1794477376 28
```
</details>

---

