---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-16 11:26:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1786893748 76
1786893753 76
1786893758 76
1786893763 76
1786893769 76
1786893774 76
1786893779 76
1786893784 76
1786893789 76
1786893794 96
1786893799 96
1786893804 96
1786893809 96
1786893814 96
1786893819 96
1786893824 96
1786893829 96
1786893834 96
1786893839 96
1786893844 96
```
</details>

---

