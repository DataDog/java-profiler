---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 00:03:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 27-34 cores)</summary>

```
1795496354 34
1795496359 34
1795496364 34
1795496369 34
1795496374 34
1795496379 34
1795496385 34
1795496390 34
1795496395 34
1795496400 34
1795496405 34
1795496410 34
1795496415 34
1795496420 34
1795496425 34
1795496430 34
1795496435 34
1795496440 34
1795496445 32
1795496450 32
```
</details>

---

