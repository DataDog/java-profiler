---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 11:36:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 8-8 cores)</summary>

```
1790782342 8
1790782347 8
1790782352 8
1790782357 8
1790782362 8
1790782367 8
1790782372 8
1790782377 8
1790782382 8
1790782387 8
1790782392 8
1790782397 8
1790782402 8
1790782407 8
1790782412 8
1790782417 8
1790782422 8
1790782427 8
1790782432 8
1790782437 8
```
</details>

---

