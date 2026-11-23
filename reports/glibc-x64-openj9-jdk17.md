---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 57-67 cores)</summary>

```
1795429067 57
1795429072 57
1795429077 57
1795429082 57
1795429087 57
1795429092 57
1795429097 57
1795429102 57
1795429107 57
1795429112 57
1795429117 57
1795429122 57
1795429127 57
1795429132 65
1795429137 65
1795429142 65
1795429147 65
1795429152 65
1795429157 65
1795429162 65
```
</details>

---

