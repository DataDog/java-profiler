---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 12:31:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1787243266 30
1787243271 30
1787243276 30
1787243281 30
1787243286 30
1787243291 30
1787243296 32
1787243301 32
1787243306 32
1787243311 32
1787243316 32
1787243321 32
1787243326 32
1787243331 32
1787243336 32
1787243341 32
1787243346 32
1787243351 32
1787243356 32
1787243361 32
```
</details>

---

