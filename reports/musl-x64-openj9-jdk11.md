---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:42:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 58-78 cores)</summary>

```
1794832684 78
1794832689 78
1794832694 78
1794832699 78
1794832704 78
1794832709 78
1794832714 78
1794832719 78
1794832724 78
1794832729 78
1794832734 78
1794832739 78
1794832744 78
1794832749 78
1794832754 78
1794832759 78
1794832764 58
1794832769 58
1794832774 58
1794832779 58
```
</details>

---

