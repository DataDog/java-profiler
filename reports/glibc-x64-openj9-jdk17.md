---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 16:29:11 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786134284 32
1786134289 32
1786134294 32
1786134299 32
1786134304 32
1786134309 32
1786134314 32
1786134319 32
1786134324 32
1786134329 32
1786134334 32
1786134339 32
1786134344 32
1786134349 32
1786134354 32
1786134359 32
1786134364 32
1786134369 30
1786134374 30
1786134379 30
```
</details>

---

