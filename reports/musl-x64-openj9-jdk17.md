---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:43:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1790678251 32
1790678256 32
1790678261 32
1790678266 32
1790678271 32
1790678276 32
1790678281 32
1790678286 32
1790678291 32
1790678296 32
1790678301 32
1790678306 32
1790678311 32
1790678316 32
1790678321 28
1790678326 28
1790678331 28
1790678336 28
1790678341 28
1790678346 28
```
</details>

---

