---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 08:17:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1795180348 30
1795180353 30
1795180358 30
1795180363 30
1795180368 30
1795180373 30
1795180378 30
1795180383 30
1795180388 30
1795180393 30
1795180398 30
1795180403 30
1795180408 28
1795180413 28
1795180418 28
1795180423 28
1795180428 28
1795180433 28
1795180438 28
1795180443 28
```
</details>

---

