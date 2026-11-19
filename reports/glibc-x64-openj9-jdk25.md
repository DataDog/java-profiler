---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 15:50:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 451 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 70-96 cores)</summary>

```
1795121157 70
1795121162 70
1795121167 73
1795121172 73
1795121177 73
1795121182 75
1795121188 75
1795121193 75
1795121198 75
1795121203 75
1795121208 75
1795121213 75
1795121218 75
1795121223 75
1795121228 75
1795121233 75
1795121238 75
1795121243 75
1795121248 75
1795121253 75
```
</details>

---

