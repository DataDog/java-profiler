---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1792676355 44
1792676360 44
1792676365 44
1792676370 44
1792676375 44
1792676380 44
1792676385 44
1792676390 44
1792676395 44
1792676400 44
1792676405 44
1792676410 44
1792676415 44
1792676420 44
1792676425 48
1792676430 48
1792676435 48
1792676440 48
1792676445 48
1792676450 48
```
</details>

---

