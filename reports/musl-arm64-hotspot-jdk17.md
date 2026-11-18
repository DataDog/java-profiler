---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 14 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (8 unique values: 18-39 cores)</summary>

```
1795010475 26
1795010480 26
1795010485 26
1795010490 26
1795010495 26
1795010500 26
1795010505 26
1795010510 26
1795010515 21
1795010520 21
1795010525 22
1795010530 22
1795010535 18
1795010540 18
1795010545 18
1795010550 18
1795010555 18
1795010560 23
1795010565 23
1795010570 39
```
</details>

---

