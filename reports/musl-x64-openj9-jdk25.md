---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:52:32 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 54-82 cores)</summary>

```
1794937533 82
1794937538 82
1794937543 80
1794937548 80
1794937553 80
1794937558 80
1794937563 82
1794937568 82
1794937573 82
1794937578 54
1794937583 54
1794937588 54
1794937593 54
1794937598 54
1794937603 54
1794937608 54
1794937613 54
1794937618 54
1794937623 54
1794937628 54
```
</details>

---

