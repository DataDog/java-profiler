---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 12:28:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 10 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 15-27 cores)</summary>

```
1788279650 15
1788279655 27
1788279660 27
1788279665 27
1788279670 27
1788279675 27
1788279680 27
1788279685 27
1788279690 27
1788279696 27
1788279701 27
1788279706 27
1788279711 27
1788279716 27
1788279721 27
1788279726 27
1788279731 27
1788279736 27
1788279741 27
1788279746 27
```
</details>

---

