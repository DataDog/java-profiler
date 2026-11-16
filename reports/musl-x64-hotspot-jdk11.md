---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:44:07 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 88-94 cores)</summary>

```
1794836312 90
1794836317 90
1794836322 90
1794836327 90
1794836332 90
1794836337 88
1794836342 88
1794836347 88
1794836352 90
1794836357 90
1794836362 90
1794836367 90
1794836373 90
1794836378 90
1794836383 90
1794836388 90
1794836393 90
1794836398 94
1794836403 94
1794836408 94
```
</details>

---

