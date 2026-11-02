---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:55:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1793634673 74
1793634678 74
1793634683 74
1793634688 74
1793634693 74
1793634698 74
1793634703 74
1793634708 76
1793634713 76
1793634719 76
1793634724 76
1793634729 76
1793634734 72
1793634739 72
1793634744 70
1793634749 70
1793634754 70
1793634759 70
1793634764 70
1793634769 70
```
</details>

---

