---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 16:08:04 EDT

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
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 5 |

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
1788293009 58
```
</details>

---

