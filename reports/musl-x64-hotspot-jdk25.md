---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:35:21 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794832263 30
1794832268 30
1794832273 30
1794832278 30
1794832283 30
1794832288 30
1794832293 30
1794832298 30
1794832303 30
1794832308 30
1794832313 32
1794832318 32
1794832323 32
1794832328 32
1794832333 30
1794832338 30
1794832343 30
1794832348 30
1794832353 30
1794832358 30
```
</details>

---

