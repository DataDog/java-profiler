---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787232419 48
1787232424 48
1787232429 48
1787232434 48
1787232439 48
1787232444 48
1787232449 43
1787232454 43
1787232459 43
1787232464 43
1787232469 43
1787232474 43
1787232479 43
1787232484 43
1787232489 43
1787232494 43
1787232499 48
1787232504 48
1787232509 48
1787232514 48
```
</details>

---

