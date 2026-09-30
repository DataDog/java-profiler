---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 05:50:42 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1790761583 36
1790761588 36
1790761593 36
1790761598 36
1790761603 36
1790761608 36
1790761613 36
1790761618 36
1790761623 36
1790761628 36
1790761633 36
1790761638 36
1790761643 36
1790761648 36
1790761653 36
1790761658 36
1790761663 36
1790761668 36
1790761673 36
1790761678 36
```
</details>

---

