---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-24 15:41:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1790278647 50
1790278652 50
1790278657 50
1790278662 50
1790278667 50
1790278672 50
1790278677 50
1790278682 50
1790278687 50
1790278692 50
1790278697 50
1790278702 50
1790278707 50
1790278712 50
1790278717 50
1790278722 50
1790278727 50
1790278732 64
1790278737 64
1790278742 64
```
</details>

---

