---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787806339 64
1787806344 64
1787806349 64
1787806354 64
1787806359 64
1787806364 64
1787806369 64
1787806374 59
1787806379 59
1787806384 59
1787806389 59
1787806394 59
1787806399 59
1787806404 59
1787806409 59
1787806414 59
1787806419 59
1787806424 59
1787806429 59
1787806434 59
```
</details>

---

