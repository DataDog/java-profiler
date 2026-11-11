---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 07:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 87-91 cores)</summary>

```
1794398951 90
1794398956 90
1794398961 90
1794398966 90
1794398971 90
1794398976 90
1794398981 91
1794398986 91
1794398991 91
1794398996 91
1794399001 91
1794399006 91
1794399011 87
1794399016 87
1794399021 87
1794399026 89
1794399031 89
1794399036 89
1794399041 89
1794399046 89
```
</details>

---

