---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-26 06:37:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1787740412 20
1787740417 20
1787740423 20
1787740428 20
1787740433 20
1787740438 20
1787740443 20
1787740448 20
1787740453 20
1787740458 20
1787740463 20
1787740468 20
1787740473 20
1787740478 20
1787740483 20
1787740488 20
1787740493 20
1787740498 20
1787740503 20
1787740508 20
```
</details>

---

