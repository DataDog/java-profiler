---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 16:08:03 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 52-64 cores)</summary>

```
1788292913 64
1788292918 64
1788292923 64
1788292928 63
1788292933 63
1788292938 63
1788292943 63
1788292948 63
1788292953 63
1788292958 63
1788292963 63
1788292968 63
1788292973 63
1788292978 63
1788292983 63
1788292988 63
1788292993 63
1788292998 58
1788293003 58
1788293008 58
```
</details>

---

