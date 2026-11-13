---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:36:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 10 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794569552 38
1794569557 38
1794569562 38
1794569567 38
1794569572 38
1794569577 38
1794569582 38
1794569587 38
1794569592 38
1794569597 38
1794569602 38
1794569607 38
1794569612 43
1794569617 43
1794569622 43
1794569627 43
1794569632 43
1794569637 43
1794569642 43
1794569647 43
```
</details>

---

