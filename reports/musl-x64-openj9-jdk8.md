---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 11:34:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1794587402 73
1794587407 73
1794587412 73
1794587417 71
1794587422 71
1794587427 71
1794587433 71
1794587438 71
1794587443 71
1794587448 73
1794587453 73
1794587458 73
1794587463 73
1794587468 73
1794587473 73
1794587478 73
1794587483 73
1794587488 73
1794587493 73
1794587498 73
```
</details>

---

