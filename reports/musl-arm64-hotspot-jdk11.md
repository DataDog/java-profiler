---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:20:12 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790853334 38
1790853339 38
1790853344 38
1790853349 38
1790853354 38
1790853359 43
1790853364 43
1790853369 38
1790853374 38
1790853379 38
1790853384 38
1790853389 38
1790853394 38
1790853399 38
1790853404 38
1790853410 38
1790853415 38
1790853420 43
1790853425 43
1790853430 43
```
</details>

---

