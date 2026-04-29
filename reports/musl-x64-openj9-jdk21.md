---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 10 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 79-84 cores)</summary>

```
1777477572 82
1777477577 82
1777477582 82
1777477587 82
1777477592 82
1777477597 82
1777477602 82
1777477607 82
1777477612 82
1777477617 79
1777477622 79
1777477627 79
1777477632 79
1777477638 79
1777477643 79
1777477648 79
1777477653 79
1777477658 79
1777477664 84
1777477669 84
```
</details>

---

