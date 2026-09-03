---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-03 15:15:24 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1788462484 44
1788462489 44
1788462494 39
1788462499 39
1788462504 39
1788462509 39
1788462514 39
1788462519 39
1788462524 39
1788462529 39
1788462534 39
1788462539 39
1788462544 39
1788462549 39
1788462554 39
1788462559 39
1788462564 39
1788462569 39
1788462574 39
1788462579 39
```
</details>

---

