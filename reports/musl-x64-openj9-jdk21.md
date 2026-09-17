---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:55:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 60-62 cores)</summary>

```
1789667362 61
1789667367 61
1789667372 61
1789667377 61
1789667382 60
1789667387 60
1789667392 60
1789667397 60
1789667402 60
1789667407 60
1789667412 60
1789667417 60
1789667422 60
1789667427 60
1789667432 60
1789667437 60
1789667442 60
1789667447 62
1789667452 62
1789667457 62
```
</details>

---

