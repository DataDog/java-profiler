---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 06:54:39 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1130 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 84-96 cores)</summary>

```
1778151001 84
1778151006 84
1778151011 84
1778151016 84
1778151021 84
1778151026 84
1778151031 84
1778151036 84
1778151041 84
1778151046 96
1778151051 96
1778151056 96
1778151061 96
1778151066 96
1778151071 96
1778151076 96
1778151081 96
1778151086 96
1778151091 96
1778151096 96
```
</details>

---

