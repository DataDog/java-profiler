---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 18:43:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 10 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794526577 48
1794526582 48
1794526587 43
1794526592 43
1794526597 43
1794526602 43
1794526607 43
1794526612 43
1794526617 43
1794526622 43
1794526627 43
1794526632 43
1794526637 43
1794526642 43
1794526647 48
1794526652 48
1794526657 48
1794526662 48
1794526667 48
1794526672 48
```
</details>

---

