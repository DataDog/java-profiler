---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 09:56:25 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795186309 50
1795186314 50
1795186319 50
1795186324 50
1795186329 50
1795186334 50
1795186339 50
1795186344 50
1795186349 50
1795186354 64
1795186359 64
1795186364 50
1795186369 50
1795186374 50
1795186379 50
1795186384 50
1795186390 50
1795186395 50
1795186400 50
1795186405 50
```
</details>

---

