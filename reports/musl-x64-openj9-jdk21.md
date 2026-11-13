---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:18:00 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 69-91 cores)</summary>

```
1794582729 91
1794582734 91
1794582739 91
1794582744 89
1794582749 89
1794582754 89
1794582759 89
1794582764 89
1794582769 71
1794582774 71
1794582779 71
1794582784 71
1794582789 71
1794582794 71
1794582799 71
1794582804 71
1794582809 71
1794582814 71
1794582819 71
1794582824 71
```
</details>

---

