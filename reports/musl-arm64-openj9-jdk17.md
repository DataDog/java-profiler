---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:36:50 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794569552 43
1794569557 43
1794569562 43
1794569567 43
1794569572 43
1794569577 43
1794569582 43
1794569587 43
1794569592 43
1794569597 43
1794569602 43
1794569607 43
1794569612 48
1794569617 48
1794569622 48
1794569627 48
1794569632 48
1794569637 48
1794569642 48
1794569647 48
```
</details>

---

