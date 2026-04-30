---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:06:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (3 unique values: 52-59 cores)</summary>

```
1777557723 54
1777557728 59
1777557733 59
1777557738 59
1777557743 59
1777557748 54
1777557753 54
1777557758 54
1777557763 54
1777557768 54
1777557773 54
1777557778 54
1777557783 54
1777557789 52
1777557794 52
1777557799 52
1777557804 52
1777557809 52
1777557814 52
1777557819 54
```
</details>

---

