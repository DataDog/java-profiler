---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:36:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 70-87 cores)</summary>

```
1795620737 70
1795620742 70
1795620748 70
1795620753 70
1795620758 87
1795620763 87
1795620768 87
1795620773 87
1795620778 87
1795620783 87
1795620788 87
1795620793 87
1795620798 87
1795620803 87
1795620808 87
1795620813 87
1795620818 87
1795620823 87
1795620828 87
1795620833 87
```
</details>

---

