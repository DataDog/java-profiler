---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:39:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787661325 94
1787661330 94
1787661335 94
1787661340 94
1787661345 94
1787661350 94
1787661355 94
1787661360 94
1787661365 94
1787661370 94
1787661375 96
1787661380 96
1787661385 96
1787661390 96
1787661395 96
1787661400 96
1787661405 96
1787661410 96
1787661415 96
1787661420 96
```
</details>

---

