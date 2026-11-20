---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 16:44:20 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 73-75 cores)</summary>

```
1795210741 73
1795210746 73
1795210751 73
1795210756 73
1795210761 73
1795210766 73
1795210771 73
1795210776 73
1795210781 73
1795210786 73
1795210791 75
1795210796 75
1795210801 75
1795210806 75
1795210811 75
1795210816 75
1795210821 75
1795210826 75
1795210831 75
1795210836 75
```
</details>

---

