---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:22:28 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 45-50 cores)</summary>

```
1770826267 45
1770826272 45
1770826277 45
1770826282 45
1770826287 45
1770826292 45
1770826297 48
1770826302 48
1770826307 48
1770826312 48
1770826317 48
1770826322 48
1770826327 48
1770826332 48
1770826337 46
1770826342 46
1770826347 50
1770826352 50
1770826357 50
1770826362 50
```
</details>

---

