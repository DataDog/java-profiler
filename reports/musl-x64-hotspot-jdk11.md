---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-24 17:04:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1777064270 20
1777064275 20
1777064280 20
1777064285 20
1777064290 20
1777064295 20
1777064300 20
1777064305 20
1777064310 29
1777064315 29
1777064320 29
1777064325 29
1777064330 29
1777064335 29
1777064340 29
1777064345 29
1777064350 29
1777064355 29
1777064360 29
1777064365 19
```
</details>

---

