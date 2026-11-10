---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:31:22 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 9 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (5 unique values: 9-15 cores)</summary>

```
1794324383 13
1794324388 13
1794324393 13
1794324398 13
1794324403 13
1794324408 13
1794324413 13
1794324418 13
1794324423 13
1794324428 11
1794324433 11
1794324438 11
1794324443 11
1794324448 10
1794324453 10
1794324458 15
1794324463 15
1794324468 10
1794324473 10
1794324478 10
```
</details>

---

