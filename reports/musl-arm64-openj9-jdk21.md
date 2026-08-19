---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 11:07:57 EDT

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
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 13 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1787151675 20
1787151680 20
1787151685 20
1787151690 20
1787151695 20
1787151700 20
1787151705 20
1787151710 20
1787151715 20
1787151720 20
1787151725 20
1787151730 20
1787151735 20
1787151740 20
1787151745 32
1787151750 32
1787151755 27
1787151760 27
1787151765 27
1787151770 27
```
</details>

---

