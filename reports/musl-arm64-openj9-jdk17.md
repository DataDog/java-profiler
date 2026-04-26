---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-26 17:09:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777237438 64
1777237443 64
1777237448 64
1777237453 64
1777237458 64
1777237463 64
1777237468 64
1777237473 64
1777237478 64
1777237483 64
1777237488 64
1777237493 64
1777237498 64
1777237503 64
1777237508 64
1777237513 64
1777237518 64
1777237523 64
1777237528 64
1777237533 64
```
</details>

---

