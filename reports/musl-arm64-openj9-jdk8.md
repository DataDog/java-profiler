---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-01 12:28:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1788279675 36
1788279680 36
1788279685 36
1788279690 36
1788279695 36
1788279700 36
1788279705 36
1788279710 36
1788279715 36
1788279720 36
1788279725 36
1788279730 36
1788279735 36
1788279740 36
1788279745 36
1788279750 36
1788279755 34
1788279760 34
1788279765 34
1788279770 34
```
</details>

---

