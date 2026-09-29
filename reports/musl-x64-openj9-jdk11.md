---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 06:43:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1790678267 53
1790678272 53
1790678277 53
1790678282 53
1790678287 53
1790678292 53
1790678297 53
1790678302 53
1790678307 53
1790678312 53
1790678317 53
1790678322 53
1790678327 53
1790678332 53
1790678337 53
1790678342 53
1790678347 53
1790678352 53
1790678357 51
1790678362 51
```
</details>

---

