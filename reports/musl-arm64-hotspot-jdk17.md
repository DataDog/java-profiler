---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 10:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 11-23 cores)</summary>

```
1795446277 23
1795446282 23
1795446287 23
1795446292 23
1795446297 23
1795446302 23
1795446307 23
1795446312 23
1795446317 23
1795446322 23
1795446327 23
1795446332 16
1795446337 16
1795446342 16
1795446347 16
1795446352 16
1795446357 16
1795446362 16
1795446368 16
1795446373 16
```
</details>

---

