---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 59-72 cores)</summary>

```
1792676330 62
1792676335 62
1792676340 62
1792676345 59
1792676350 59
1792676355 59
1792676360 59
1792676365 65
1792676370 65
1792676375 65
1792676380 65
1792676385 65
1792676390 65
1792676395 65
1792676400 65
1792676405 65
1792676410 72
1792676415 72
1792676420 72
1792676425 72
```
</details>

---

