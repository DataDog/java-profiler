---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:28:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 10 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790241530 46
1790241535 46
1790241540 46
1790241545 46
1790241550 46
1790241555 46
1790241561 46
1790241566 46
1790241571 48
1790241576 48
1790241581 48
1790241586 48
1790241591 48
1790241596 48
1790241601 43
1790241606 43
1790241611 43
1790241616 43
1790241621 43
1790241626 43
```
</details>

---

