---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-29 05:48:00 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 8 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787996595 66
1787996600 66
1787996605 66
1787996610 66
1787996615 66
1787996620 66
1787996625 66
1787996630 66
1787996635 66
1787996640 66
1787996645 66
1787996650 66
1787996655 66
1787996660 64
1787996665 64
1787996670 64
1787996675 64
1787996680 64
1787996685 64
1787996690 64
```
</details>

---

