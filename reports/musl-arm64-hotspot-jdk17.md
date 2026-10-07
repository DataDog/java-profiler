---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1791391389 53
1791391394 53
1791391399 53
1791391404 53
1791391409 53
1791391414 64
1791391419 64
1791391424 64
1791391429 64
1791391434 51
1791391439 51
1791391444 51
1791391449 51
1791391454 51
1791391459 51
1791391464 51
1791391469 51
1791391474 51
1791391479 51
1791391484 51
```
</details>

---

