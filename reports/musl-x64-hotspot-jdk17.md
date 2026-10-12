---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 04:43:02 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 54-63 cores)</summary>

```
1791794282 63
1791794287 63
1791794292 63
1791794297 63
1791794302 63
1791794307 63
1791794312 63
1791794317 63
1791794322 63
1791794327 63
1791794332 63
1791794337 63
1791794342 63
1791794347 63
1791794352 63
1791794357 61
1791794362 61
1791794367 61
1791794372 61
1791794377 56
```
</details>

---

