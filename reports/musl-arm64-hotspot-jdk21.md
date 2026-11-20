---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-20 09:57:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 14-14 cores)</summary>

```
1795186267 14
1795186272 14
1795186277 14
1795186282 14
1795186287 14
1795186292 14
1795186298 14
1795186303 14
1795186308 14
1795186313 14
1795186318 14
1795186323 14
1795186328 14
1795186333 14
1795186338 14
1795186343 14
1795186348 14
1795186353 14
1795186358 14
1795186363 14
```
</details>

---

