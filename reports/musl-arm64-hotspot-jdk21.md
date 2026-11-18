---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:37:30 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 14 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795008423 29
1795008428 29
1795008433 29
1795008438 29
1795008443 29
1795008448 34
1795008453 34
1795008458 34
1795008463 34
1795008468 34
1795008473 34
1795008478 34
1795008483 34
1795008488 34
1795008493 34
1795008498 34
1795008503 34
1795008508 34
1795008513 34
1795008518 34
```
</details>

---

