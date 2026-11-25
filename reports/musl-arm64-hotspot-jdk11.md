---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:18:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 27-47 cores)</summary>

```
1795641269 27
1795641274 27
1795641279 27
1795641284 27
1795641289 47
1795641294 47
1795641299 47
1795641304 47
1795641309 47
1795641314 33
1795641319 33
1795641324 33
1795641329 33
1795641334 33
1795641339 33
1795641344 33
1795641349 33
1795641354 33
1795641359 33
1795641364 33
```
</details>

---

