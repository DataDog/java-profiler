---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:26:04 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1794489698 86
1794489703 86
1794489708 86
1794489713 86
1794489718 86
1794489723 86
1794489728 86
1794489733 86
1794489738 86
1794489743 86
1794489748 84
1794489753 84
1794489758 84
1794489763 84
1794489768 84
1794489773 84
1794489778 84
1794489783 84
1794489788 84
1794489793 84
```
</details>

---

