---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 03:57:41 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 52-59 cores)</summary>

```
1778572304 59
1778572309 59
1778572314 59
1778572319 59
1778572324 59
1778572329 59
1778572334 59
1778572339 59
1778572344 59
1778572349 59
1778572354 59
1778572359 59
1778572364 52
1778572369 52
1778572374 52
1778572379 52
1778572384 52
1778572389 52
1778572394 52
1778572399 52
```
</details>

---

