---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1790346446 33
1790346451 33
1790346456 33
1790346461 33
1790346466 33
1790346471 33
1790346476 33
1790346481 33
1790346486 33
1790346491 33
1790346496 33
1790346501 33
1790346506 33
1790346511 33
1790346516 33
1790346521 38
1790346526 38
1790346531 38
1790346536 38
1790346541 38
```
</details>

---

