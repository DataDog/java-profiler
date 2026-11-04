---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 15:01:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793822227 48
1793822232 48
1793822237 48
1793822242 48
1793822247 48
1793822252 48
1793822257 48
1793822262 48
1793822267 48
1793822272 48
1793822277 48
1793822282 48
1793822287 48
1793822292 48
1793822297 48
1793822302 48
1793822307 48
1793822312 48
1793822317 48
1793822322 48
```
</details>

---

