---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:24:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 12 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1795184355 27
1795184360 27
1795184365 27
1795184370 27
1795184375 27
1795184380 27
1795184385 27
1795184390 27
1795184395 27
1795184400 27
1795184405 27
1795184410 27
1795184415 27
1795184420 27
1795184425 27
1795184430 27
1795184435 27
1795184440 29
1795184445 29
1795184450 29
```
</details>

---

