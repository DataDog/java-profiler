---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-24 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1792835483 70
1792835488 70
1792835493 70
1792835498 70
1792835503 70
1792835508 70
1792835513 72
1792835518 72
1792835523 72
1792835528 72
1792835533 72
1792835538 72
1792835543 72
1792835548 72
1792835553 72
1792835558 72
1792835563 72
1792835568 72
1792835573 72
1792835578 72
```
</details>

---

