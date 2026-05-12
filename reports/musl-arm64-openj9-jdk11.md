---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 04:02:15 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1778572524 51
1778572529 51
1778572534 51
1778572539 51
1778572544 51
1778572549 51
1778572554 51
1778572559 51
1778572564 51
1778572569 51
1778572574 51
1778572579 51
1778572584 51
1778572589 51
1778572594 51
1778572599 51
1778572604 51
1778572609 51
1778572614 51
1778572619 51
```
</details>

---

