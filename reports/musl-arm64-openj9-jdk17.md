---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790678267 43
1790678272 43
1790678277 43
1790678282 43
1790678287 48
1790678292 48
1790678297 48
1790678302 43
1790678307 43
1790678312 43
1790678317 43
1790678322 43
1790678327 43
1790678332 43
1790678337 43
1790678342 48
1790678347 48
1790678352 46
1790678357 46
1790678362 46
```
</details>

---

