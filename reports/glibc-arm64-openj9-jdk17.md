---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 05:49:11 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1788342321 44
1788342326 44
1788342331 44
1788342336 44
1788342341 44
1788342346 44
1788342351 44
1788342356 44
1788342361 44
1788342366 44
1788342371 39
1788342376 39
1788342381 39
1788342386 39
1788342391 39
1788342396 39
1788342401 39
1788342406 39
1788342411 39
1788342416 39
```
</details>

---

