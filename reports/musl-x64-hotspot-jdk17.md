---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 12:32:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793031980 30
1793031985 30
1793031990 30
1793031995 30
1793032000 30
1793032005 28
1793032010 28
1793032015 28
1793032020 28
1793032025 28
1793032030 28
1793032035 28
1793032040 28
1793032045 28
1793032050 28
1793032055 28
1793032060 28
1793032065 30
1793032070 30
1793032075 30
```
</details>

---

