---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 10 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787806339 29
1787806344 29
1787806349 34
1787806354 34
1787806359 34
1787806364 34
1787806369 34
1787806374 34
1787806379 34
1787806384 34
1787806389 34
1787806394 34
1787806399 34
1787806404 34
1787806409 34
1787806414 34
1787806419 34
1787806424 34
1787806429 34
1787806434 34
```
</details>

---

