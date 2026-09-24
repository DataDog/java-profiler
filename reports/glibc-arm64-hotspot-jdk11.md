---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (4 unique values: 34-48 cores)</summary>

```
1790238270 48
1790238275 48
1790238280 48
1790238285 48
1790238290 48
1790238295 48
1790238300 44
1790238305 44
1790238310 39
1790238315 39
1790238320 39
1790238325 39
1790238330 39
1790238335 39
1790238340 39
1790238345 39
1790238350 39
1790238355 39
1790238360 39
1790238365 34
```
</details>

---

