---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:14:21 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 56-59 cores)</summary>

```
1795108223 56
1795108228 56
1795108233 59
1795108238 59
1795108243 59
1795108248 59
1795108253 59
1795108258 59
1795108263 56
1795108268 56
1795108273 56
1795108278 56
1795108283 56
1795108288 56
1795108293 56
1795108298 56
1795108303 56
1795108308 56
1795108313 56
1795108318 56
```
</details>

---

