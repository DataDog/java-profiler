---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 10 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795442335 48
1795442340 48
1795442345 48
1795442350 48
1795442355 48
1795442360 48
1795442365 48
1795442370 48
1795442375 48
1795442380 48
1795442385 48
1795442390 48
1795442395 48
1795442400 64
1795442405 64
1795442410 64
1795442415 64
1795442420 64
1795442425 64
1795442430 64
```
</details>

---

