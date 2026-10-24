---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-24 05:16:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 10 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (4 unique values: 40-43 cores)</summary>

```
1792833210 40
1792833215 42
1792833220 42
1792833225 42
1792833230 42
1792833235 42
1792833240 42
1792833245 41
1792833250 41
1792833255 41
1792833260 41
1792833265 41
1792833270 41
1792833275 41
1792833280 41
1792833285 41
1792833290 41
1792833295 41
1792833300 41
1792833305 41
```
</details>

---

