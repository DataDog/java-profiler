---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-14 10:14:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786716569 48
1786716574 48
1786716579 48
1786716584 48
1786716589 48
1786716594 48
1786716599 48
1786716604 43
1786716609 43
1786716614 43
1786716619 43
1786716624 43
1786716629 43
1786716634 43
1786716639 43
1786716644 43
1786716649 43
1786716654 43
1786716659 48
1786716664 48
```
</details>

---

