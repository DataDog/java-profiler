---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 09:55:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787147486 96
1787147491 94
1787147496 94
1787147501 94
1787147506 94
1787147511 94
1787147516 94
1787147521 94
1787147526 94
1787147531 94
1787147536 94
1787147541 96
1787147546 96
1787147551 96
1787147556 96
1787147561 96
1787147566 96
1787147571 96
1787147576 96
1787147581 96
```
</details>

---

