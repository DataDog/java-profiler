---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:42:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794832689 32
1794832694 32
1794832699 30
1794832704 30
1794832709 30
1794832714 30
1794832719 30
1794832724 30
1794832729 30
1794832734 30
1794832739 30
1794832744 30
1794832749 30
1794832754 30
1794832759 30
1794832764 30
1794832769 30
1794832774 30
1794832779 30
1794832785 30
```
</details>

---

