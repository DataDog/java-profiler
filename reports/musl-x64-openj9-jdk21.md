---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:14:04 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1795169249 62
1795169254 62
1795169259 62
1795169264 62
1795169269 62
1795169274 62
1795169279 62
1795169284 62
1795169289 62
1795169294 62
1795169299 62
1795169304 62
1795169309 62
1795169314 62
1795169319 64
1795169324 64
1795169329 66
1795169334 66
1795169339 66
1795169344 66
```
</details>

---

