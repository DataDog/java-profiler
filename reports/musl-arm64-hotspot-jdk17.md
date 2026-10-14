---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 08:32:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1791980547 27
1791980552 27
1791980557 27
1791980562 27
1791980567 27
1791980572 27
1791980577 22
1791980582 22
1791980587 22
1791980592 22
1791980597 22
1791980602 22
1791980607 22
1791980612 22
1791980617 22
1791980622 22
1791980627 22
1791980632 22
1791980637 22
1791980642 22
```
</details>

---

