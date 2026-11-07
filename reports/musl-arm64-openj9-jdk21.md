---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-07 00:04:51 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794027632 48
1794027637 48
1794027642 48
1794027647 48
1794027652 48
1794027657 48
1794027662 48
1794027667 48
1794027672 48
1794027677 48
1794027682 48
1794027687 48
1794027692 48
1794027697 48
1794027702 48
1794027707 48
1794027712 48
1794027717 48
1794027722 48
1794027727 48
```
</details>

---

