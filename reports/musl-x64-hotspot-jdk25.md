---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 29.40/sec |
| Health Score | 1837% |
| Threads | 12 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1122 |
| Sample Rate | 37.40/sec |
| Health Score | 2337% |
| Threads | 13 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (6 unique values: 58-84 cores)</summary>

```
1769708272 60
1769708277 60
1769708282 60
1769708287 60
1769708292 58
1769708297 58
1769708302 58
1769708307 58
1769708312 58
1769708317 58
1769708322 58
1769708327 58
1769708332 58
1769708337 58
1769708342 58
1769708347 58
1769708352 58
1769708357 78
1769708362 78
1769708367 77
```
</details>

---

