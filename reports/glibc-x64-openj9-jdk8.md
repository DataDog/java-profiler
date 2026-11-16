---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 07:35:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1794832277 32
1794832282 32
1794832287 32
1794832292 32
1794832297 32
1794832302 32
1794832307 32
1794832312 32
1794832317 32
1794832322 32
1794832327 32
1794832332 27
1794832337 27
1794832342 27
1794832347 27
1794832352 27
1794832357 27
1794832362 27
1794832367 27
1794832372 27
```
</details>

---

