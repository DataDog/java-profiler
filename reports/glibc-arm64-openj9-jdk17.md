---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-25 08:39:35 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1787661364 40
1787661369 40
1787661374 40
1787661379 40
1787661384 40
1787661389 40
1787661394 40
1787661399 40
1787661404 40
1787661409 40
1787661414 40
1787661419 40
1787661424 40
1787661429 40
1787661434 40
1787661439 40
1787661444 40
1787661449 40
1787661454 40
1787661459 40
```
</details>

---

