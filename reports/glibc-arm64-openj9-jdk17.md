---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 11:09:33 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (4 unique values: 15-29 cores)</summary>

```
1790262257 29
1790262262 29
1790262267 29
1790262272 29
1790262277 29
1790262282 23
1790262287 23
1790262292 23
1790262297 23
1790262302 23
1790262307 23
1790262312 24
1790262317 24
1790262322 15
1790262327 15
1790262332 15
1790262337 15
1790262342 15
1790262347 15
1790262352 15
```
</details>

---

