---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:39:36 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 16-48 cores)</summary>

```
1787661329 48
1787661334 48
1787661339 16
1787661344 16
1787661349 16
1787661354 16
1787661359 16
1787661364 16
1787661369 16
1787661374 16
1787661379 16
1787661384 16
1787661389 16
1787661394 16
1787661399 16
1787661404 16
1787661409 32
1787661414 32
1787661419 41
1787661424 41
```
</details>

---

