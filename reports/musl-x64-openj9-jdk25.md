---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-12 08:26:05 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1794489683 85
1794489688 85
1794489693 85
1794489698 85
1794489703 85
1794489708 85
1794489713 85
1794489718 85
1794489723 87
1794489728 87
1794489733 87
1794489738 87
1794489743 87
1794489748 87
1794489753 87
1794489758 87
1794489763 87
1794489768 87
1794489773 87
1794489778 89
```
</details>

---

