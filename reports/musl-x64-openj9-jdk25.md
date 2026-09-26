---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-26 01:03:14 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (5 unique values: 62-79 cores)</summary>

```
1790398378 72
1790398383 76
1790398388 76
1790398393 76
1790398398 76
1790398403 76
1790398408 76
1790398413 76
1790398418 76
1790398423 76
1790398428 76
1790398433 76
1790398438 64
1790398443 64
1790398448 62
1790398453 62
1790398458 62
1790398463 62
1790398468 62
1790398473 62
```
</details>

---

