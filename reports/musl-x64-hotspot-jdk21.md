---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 07:29:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 42-63 cores)</summary>

```
1791372302 42
1791372307 42
1791372312 42
1791372317 42
1791372322 42
1791372327 42
1791372332 42
1791372337 42
1791372342 42
1791372347 42
1791372352 42
1791372357 42
1791372362 42
1791372368 63
1791372373 63
1791372378 63
1791372383 63
1791372388 63
1791372393 63
1791372398 63
```
</details>

---

