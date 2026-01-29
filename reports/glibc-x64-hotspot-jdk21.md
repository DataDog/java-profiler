---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:43:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 17.10/sec |
| Health Score | 1069% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 22.97/sec |
| Health Score | 1436% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1769708252 28
1769708257 28
1769708262 26
1769708267 26
1769708272 26
1769708277 26
1769708282 30
1769708287 30
1769708292 30
1769708297 30
1769708302 30
1769708307 30
1769708312 30
1769708317 30
1769708322 32
1769708327 32
1769708332 32
1769708337 32
1769708342 32
1769708347 32
```
</details>

---

