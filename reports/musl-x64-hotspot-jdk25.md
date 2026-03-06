---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:52:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 19-32 cores)</summary>

```
1772790348 19
1772790353 19
1772790358 19
1772790363 19
1772790368 21
1772790373 21
1772790378 21
1772790383 21
1772790388 21
1772790393 21
1772790398 21
1772790403 21
1772790408 23
1772790413 23
1772790418 27
1772790423 27
1772790428 27
1772790433 27
1772790438 27
1772790443 27
```
</details>

---

