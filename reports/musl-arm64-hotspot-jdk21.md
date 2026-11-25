---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:34:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795613380 59
1795613385 59
1795613390 59
1795613395 59
1795613400 59
1795613405 59
1795613410 59
1795613415 59
1795613420 59
1795613425 59
1795613430 59
1795613435 59
1795613440 59
1795613445 59
1795613450 64
1795613455 64
1795613460 64
1795613465 64
1795613470 64
1795613475 64
```
</details>

---

