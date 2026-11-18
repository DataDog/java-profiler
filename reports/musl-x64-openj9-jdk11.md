---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:31:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 42-64 cores)</summary>

```
1795008248 42
1795008253 42
1795008258 42
1795008263 42
1795008268 42
1795008273 42
1795008278 42
1795008283 42
1795008288 42
1795008293 42
1795008298 42
1795008303 42
1795008308 42
1795008313 42
1795008318 42
1795008323 42
1795008328 42
1795008333 42
1795008338 42
1795008343 42
```
</details>

---

