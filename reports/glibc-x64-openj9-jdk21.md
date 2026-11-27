---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 11:28:40 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 4 |
| Sample Rate | 0.07/sec |
| Health Score | 4% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 65-73 cores)</summary>

```
1795796647 67
1795796652 67
1795796657 65
1795796662 65
1795796667 65
1795796672 65
1795796677 73
1795796682 73
1795796687 73
1795796692 73
1795796697 73
1795796702 73
1795796707 73
1795796712 73
1795796717 73
1795796722 73
1795796727 73
1795796732 73
1795796737 73
1795796742 73
```
</details>

---

