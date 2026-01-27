---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 18.73/sec |
| Health Score | 1171% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 25.90/sec |
| Health Score | 1619% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 23-33 cores)</summary>

```
1769514225 23
1769514230 23
1769514235 23
1769514240 23
1769514245 23
1769514250 23
1769514255 23
1769514260 23
1769514265 23
1769514270 27
1769514275 27
1769514280 33
1769514285 33
1769514290 33
1769514295 33
1769514300 33
1769514305 33
1769514310 33
1769514315 33
1769514320 31
```
</details>

---

