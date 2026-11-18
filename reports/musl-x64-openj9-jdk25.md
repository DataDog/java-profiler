---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:31:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 61-96 cores)</summary>

```
1795008338 96
1795008343 96
1795008348 96
1795008353 96
1795008358 96
1795008363 63
1795008368 63
1795008373 63
1795008378 63
1795008383 63
1795008388 63
1795008393 63
1795008398 63
1795008403 63
1795008408 63
1795008413 63
1795008418 63
1795008423 63
1795008428 63
1795008433 63
```
</details>

---

