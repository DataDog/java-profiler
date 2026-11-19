---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:29:53 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 51-55 cores)</summary>

```
1795098295 53
1795098300 53
1795098305 53
1795098310 53
1795098315 53
1795098320 53
1795098325 53
1795098330 53
1795098335 53
1795098340 51
1795098345 51
1795098350 51
1795098355 53
1795098360 53
1795098365 55
1795098370 55
1795098375 55
1795098380 55
1795098385 55
1795098390 55
```
</details>

---

