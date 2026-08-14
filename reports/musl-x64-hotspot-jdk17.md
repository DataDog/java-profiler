---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-14 01:01:25 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1786683297 20
1786683302 20
1786683307 20
1786683312 20
1786683317 20
1786683322 20
1786683327 20
1786683332 20
1786683337 32
1786683342 32
1786683347 32
1786683352 32
1786683357 32
1786683362 32
1786683367 32
1786683372 32
1786683377 32
1786683382 32
1786683387 32
1786683392 32
```
</details>

---

