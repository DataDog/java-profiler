---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 10:24:02 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 20-28 cores)</summary>

```
1795533349 28
1795533354 28
1795533359 28
1795533364 28
1795533369 28
1795533374 28
1795533379 28
1795533385 28
1795533390 28
1795533395 28
1795533400 28
1795533405 28
1795533410 28
1795533415 28
1795533420 28
1795533425 28
1795533430 28
1795533435 20
1795533440 20
1795533445 25
```
</details>

---

