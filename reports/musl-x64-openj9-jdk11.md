---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:02:31 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1794405409 91
1794405414 91
1794405419 91
1794405424 91
1794405429 91
1794405434 91
1794405439 91
1794405444 91
1794405449 91
1794405454 91
1794405459 91
1794405464 91
1794405469 91
1794405474 91
1794405480 91
1794405485 91
1794405490 91
1794405495 87
1794405500 87
1794405505 87
```
</details>

---

