---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 08:53:21 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794318474 43
1794318479 43
1794318484 48
1794318489 48
1794318494 48
1794318499 48
1794318504 48
1794318509 48
1794318514 48
1794318519 48
1794318524 48
1794318529 48
1794318534 48
1794318539 48
1794318544 48
1794318549 48
1794318554 48
1794318559 48
1794318564 48
1794318569 48
```
</details>

---

