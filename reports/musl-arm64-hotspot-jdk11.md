---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:09:56 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 13 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795129541 50
1795129546 50
1795129551 50
1795129556 50
1795129561 50
1795129566 50
1795129571 50
1795129576 50
1795129581 50
1795129586 50
1795129591 50
1795129596 50
1795129601 50
1795129606 64
1795129611 64
1795129616 64
1795129621 64
1795129626 64
1795129631 64
1795129636 64
```
</details>

---

