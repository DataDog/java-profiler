---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 00:04:51 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 10 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1794027632 34
1794027637 34
1794027642 34
1794027647 14
1794027652 14
1794027657 14
1794027662 14
1794027667 14
1794027672 14
1794027677 14
1794027682 14
1794027687 14
1794027692 14
1794027697 14
1794027702 14
1794027707 14
1794027712 14
1794027718 14
1794027723 14
1794027728 14
```
</details>

---

