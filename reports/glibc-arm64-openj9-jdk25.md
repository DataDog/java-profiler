---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:35:21 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1789673391 64
1789673396 64
1789673401 64
1789673406 64
1789673411 64
1789673416 64
1789673421 64
1789673426 64
1789673431 64
1789673436 64
1789673441 64
1789673446 64
1789673451 64
1789673456 64
1789673461 64
1789673466 64
1789673471 52
1789673476 52
1789673481 52
1789673486 52
```
</details>

---

