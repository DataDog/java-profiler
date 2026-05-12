---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:19:45 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 955 |
| Sample Rate | 15.92/sec |
| Health Score | 995% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1778577308 28
1778577313 32
1778577318 32
1778577323 32
1778577328 32
1778577333 32
1778577338 32
1778577343 32
1778577348 32
1778577353 32
1778577358 32
1778577363 32
1778577368 32
1778577373 30
1778577378 30
1778577383 30
1778577388 30
1778577393 30
1778577398 30
1778577403 30
```
</details>

---

