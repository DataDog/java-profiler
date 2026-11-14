---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 16:39:49 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794692113 92
1794692118 92
1794692123 92
1794692128 92
1794692133 92
1794692138 92
1794692143 92
1794692148 92
1794692153 92
1794692158 92
1794692163 92
1794692168 92
1794692173 92
1794692178 92
1794692183 92
1794692188 92
1794692193 94
1794692198 94
1794692203 94
1794692208 94
```
</details>

---

