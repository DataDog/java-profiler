---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 01:04:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787720260 40
1787720265 40
1787720270 40
1787720275 40
1787720280 40
1787720285 40
1787720290 48
1787720295 48
1787720300 48
1787720305 48
1787720310 48
1787720315 48
1787720320 48
1787720325 48
1787720330 48
1787720335 48
1787720340 48
1787720345 48
1787720350 48
1787720355 48
```
</details>

---

