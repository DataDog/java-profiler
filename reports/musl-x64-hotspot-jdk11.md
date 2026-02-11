---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:22:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 43-60 cores)</summary>

```
1770826257 43
1770826262 43
1770826267 43
1770826272 43
1770826277 43
1770826282 43
1770826287 43
1770826292 43
1770826297 43
1770826302 43
1770826307 43
1770826312 43
1770826317 43
1770826322 43
1770826327 60
1770826332 60
1770826337 60
1770826342 60
1770826347 60
1770826352 60
```
</details>

---

