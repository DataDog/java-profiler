---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:42:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795538314 32
1795538319 32
1795538324 32
1795538329 32
1795538334 32
1795538339 32
1795538344 32
1795538349 32
1795538354 32
1795538359 32
1795538364 32
1795538369 32
1795538374 32
1795538379 32
1795538384 32
1795538389 32
1795538394 32
1795538399 32
1795538404 32
1795538409 32
```
</details>

---

