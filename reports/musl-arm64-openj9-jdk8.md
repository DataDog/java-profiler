---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1790678277 32
1790678282 32
1790678287 32
1790678292 32
1790678297 32
1790678302 32
1790678307 32
1790678312 32
1790678317 32
1790678322 32
1790678327 32
1790678332 32
1790678337 32
1790678342 32
1790678347 32
1790678352 32
1790678357 32
1790678362 32
1790678367 32
1790678372 32
```
</details>

---

