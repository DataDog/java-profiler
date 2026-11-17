---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:52:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794937528 51
1794937533 51
1794937538 51
1794937543 51
1794937548 51
1794937553 51
1794937558 51
1794937563 51
1794937568 51
1794937573 51
1794937578 51
1794937583 51
1794937588 51
1794937593 51
1794937598 51
1794937603 51
1794937608 51
1794937613 51
1794937618 51
1794937623 51
```
</details>

---

