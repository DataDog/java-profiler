---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-20 05:46:33 EDT

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
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1789897342 29
1789897347 29
1789897352 29
1789897357 29
1789897362 29
1789897367 29
1789897372 29
1789897377 29
1789897382 29
1789897387 29
1789897392 29
1789897397 29
1789897402 29
1789897407 29
1789897412 29
1789897417 34
1789897422 34
1789897427 34
1789897432 34
1789897437 34
```
</details>

---

