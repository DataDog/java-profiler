---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:41:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 76-87 cores)</summary>

```
1795199758 83
1795199763 83
1795199768 83
1795199773 83
1795199778 85
1795199783 85
1795199788 85
1795199793 85
1795199798 85
1795199803 85
1795199808 76
1795199813 76
1795199818 76
1795199823 76
1795199828 76
1795199833 78
1795199838 78
1795199843 78
1795199848 78
1795199853 78
```
</details>

---

