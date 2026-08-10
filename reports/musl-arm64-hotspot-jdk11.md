---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 06:10:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 22-23 cores)</summary>

```
1786356312 22
1786356317 22
1786356322 22
1786356327 22
1786356332 22
1786356337 22
1786356342 22
1786356347 22
1786356352 22
1786356357 23
1786356362 23
1786356367 23
1786356372 23
1786356377 23
1786356382 23
1786356387 23
1786356392 22
1786356397 22
1786356402 22
1786356407 22
```
</details>

---

