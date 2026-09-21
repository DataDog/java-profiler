---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-20 21:19:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789953269 32
1789953274 32
1789953279 32
1789953284 32
1789953289 32
1789953294 32
1789953299 32
1789953304 32
1789953309 32
1789953314 32
1789953319 32
1789953324 32
1789953329 32
1789953334 32
1789953339 32
1789953344 32
1789953349 32
1789953354 32
1789953359 32
1789953364 32
```
</details>

---

