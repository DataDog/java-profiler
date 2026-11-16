---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:35:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1794832277 16
1794832282 16
1794832287 16
1794832292 16
1794832297 16
1794832302 16
1794832307 16
1794832312 16
1794832317 16
1794832322 16
1794832327 16
1794832332 18
1794832337 18
1794832342 18
1794832347 18
1794832352 18
1794832357 18
1794832362 18
1794832367 18
1794832372 18
```
</details>

---

