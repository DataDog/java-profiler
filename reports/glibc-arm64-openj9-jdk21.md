---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 09:24:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 10 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795184386 50
1795184391 50
1795184396 50
1795184401 36
1795184406 36
1795184411 36
1795184416 36
1795184421 36
1795184426 36
1795184431 36
1795184436 36
1795184441 36
1795184446 36
1795184451 36
1795184456 36
1795184461 36
1795184466 36
1795184471 36
1795184476 36
1795184481 36
```
</details>

---

