---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 93 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1786526129 49
1786526134 49
1786526139 49
1786526144 49
1786526149 49
1786526154 49
1786526159 49
1786526164 49
1786526169 49
1786526174 49
1786526179 49
1786526184 49
1786526189 49
1786526194 49
1786526199 49
1786526204 49
1786526209 49
1786526214 51
1786526219 51
1786526224 51
```
</details>

---

