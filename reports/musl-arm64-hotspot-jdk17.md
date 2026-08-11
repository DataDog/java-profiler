---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:44:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786455562 46
1786455567 46
1786455572 46
1786455577 46
1786455582 46
1786455587 46
1786455592 51
1786455597 51
1786455602 51
1786455607 51
1786455612 51
1786455617 51
1786455622 51
1786455627 51
1786455632 51
1786455637 51
1786455642 51
1786455647 51
1786455652 51
1786455657 51
```
</details>

---

