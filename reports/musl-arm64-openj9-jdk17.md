---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-20 21:19:10 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 17-52 cores)</summary>

```
1789953263 22
1789953268 22
1789953273 22
1789953278 22
1789953283 22
1789953288 22
1789953293 22
1789953298 22
1789953303 22
1789953308 22
1789953313 22
1789953318 17
1789953323 17
1789953328 17
1789953333 47
1789953338 47
1789953343 47
1789953348 47
1789953353 47
1789953358 47
```
</details>

---

