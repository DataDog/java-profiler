---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:12:30 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 32-46 cores)</summary>

```
1795097307 32
1795097312 32
1795097317 32
1795097323 32
1795097328 32
1795097333 32
1795097338 32
1795097343 32
1795097348 46
1795097353 46
1795097358 46
1795097363 46
1795097368 46
1795097373 46
1795097378 46
1795097383 46
1795097388 46
1795097393 46
1795097398 46
1795097403 46
```
</details>

---

