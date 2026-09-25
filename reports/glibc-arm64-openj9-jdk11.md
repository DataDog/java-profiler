---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 10:31:16 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790346416 43
1790346421 43
1790346426 43
1790346431 43
1790346436 48
1790346441 48
1790346446 48
1790346451 48
1790346456 48
1790346461 48
1790346466 48
1790346471 48
1790346476 48
1790346481 48
1790346486 43
1790346491 43
1790346496 43
1790346501 43
1790346506 43
1790346511 43
```
</details>

---

