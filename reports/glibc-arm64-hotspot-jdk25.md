---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 10:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 52-52 cores)</summary>

```
1795446377 52
1795446382 52
1795446387 52
1795446392 52
1795446397 52
1795446402 52
1795446407 52
1795446412 52
1795446417 52
1795446422 52
1795446427 52
1795446432 52
1795446437 52
1795446442 52
1795446447 52
1795446452 52
1795446457 52
1795446462 52
1795446467 52
1795446472 52
```
</details>

---

