---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 15:01:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793822217 32
1793822222 32
1793822227 32
1793822232 32
1793822237 32
1793822242 32
1793822247 32
1793822252 32
1793822257 32
1793822262 32
1793822267 32
1793822272 32
1793822277 32
1793822282 32
1793822287 32
1793822292 32
1793822297 32
1793822302 32
1793822307 32
1793822312 32
```
</details>

---

