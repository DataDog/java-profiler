---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 05:49:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1788342276 42
1788342281 42
1788342286 42
1788342291 42
1788342296 42
1788342301 42
1788342306 42
1788342311 42
1788342316 42
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
1788342371 44
```
</details>

---

