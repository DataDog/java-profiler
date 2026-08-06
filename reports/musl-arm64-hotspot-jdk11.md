---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 06:20:06 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 11 |
| Allocations | 192 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (5 unique values: 30-38 cores)</summary>

```
1786011330 35
1786011335 35
1786011340 35
1786011345 35
1786011350 35
1786011355 35
1786011360 35
1786011365 35
1786011370 35
1786011375 35
1786011380 35
1786011385 35
1786011390 35
1786011395 35
1786011400 38
1786011405 38
1786011410 36
1786011416 36
1786011421 36
1786011426 36
```
</details>

---

