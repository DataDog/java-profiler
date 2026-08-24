---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 17:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787605375 64
1787605380 64
1787605385 64
1787605390 64
1787605395 64
1787605400 64
1787605405 64
1787605410 64
1787605415 64
1787605420 64
1787605425 64
1787605430 64
1787605435 64
1787605440 64
1787605445 64
1787605450 64
1787605455 64
1787605460 64
1787605465 64
1787605470 64
```
</details>

---

