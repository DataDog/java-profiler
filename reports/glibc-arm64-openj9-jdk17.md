---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:47:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 9 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 15-50 cores)</summary>

```
1795099264 15
1795099269 15
1795099274 15
1795099279 15
1795099284 15
1795099289 50
1795099294 50
1795099299 50
1795099304 50
1795099309 50
1795099314 50
1795099319 50
1795099324 50
1795099329 50
1795099334 50
1795099339 50
1795099344 50
1795099349 50
1795099354 50
1795099359 50
```
</details>

---

