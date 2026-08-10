---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:46:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1786376376 53
1786376381 53
1786376386 53
1786376391 53
1786376396 53
1786376401 53
1786376406 53
1786376411 64
1786376416 64
1786376421 64
1786376426 64
1786376431 51
1786376436 51
1786376441 51
1786376446 51
1786376451 51
1786376456 46
1786376461 46
1786376466 46
1786376471 46
```
</details>

---

