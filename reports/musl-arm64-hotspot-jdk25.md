---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:42:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778582309 64
1778582314 64
1778582319 64
1778582324 64
1778582329 64
1778582334 64
1778582339 64
1778582344 64
1778582349 64
1778582354 64
1778582359 64
1778582364 64
1778582369 64
1778582374 64
1778582379 64
1778582384 64
1778582389 64
1778582394 64
1778582399 64
1778582404 64
```
</details>

---

