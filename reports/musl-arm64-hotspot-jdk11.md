---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:34:09 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793125635 48
1793125640 48
1793125645 48
1793125650 48
1793125655 48
1793125660 48
1793125665 48
1793125670 48
1793125675 48
1793125680 48
1793125685 48
1793125690 48
1793125695 48
1793125700 48
1793125705 48
1793125710 48
1793125715 48
1793125720 48
1793125725 48
1793125730 48
```
</details>

---

