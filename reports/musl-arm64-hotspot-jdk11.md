---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 01:04:36 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (3 unique values: 8-18 cores)</summary>

```
1793336408 8
1793336413 8
1793336418 8
1793336423 8
1793336428 8
1793336433 13
1793336438 13
1793336443 8
1793336448 8
1793336453 8
1793336458 8
1793336463 8
1793336468 8
1793336473 8
1793336478 8
1793336483 13
1793336488 13
1793336493 8
1793336498 8
1793336503 8
```
</details>

---

