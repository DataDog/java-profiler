---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-22 20:12:38 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787443522 32
1787443527 32
1787443532 32
1787443537 32
1787443542 32
1787443547 32
1787443552 32
1787443557 32
1787443562 32
1787443567 32
1787443572 32
1787443577 32
1787443582 32
1787443587 32
1787443592 32
1787443597 32
1787443602 32
1787443607 32
1787443613 32
1787443618 32
```
</details>

---

