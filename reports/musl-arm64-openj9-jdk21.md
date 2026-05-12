---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 08:29:47 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778588559 59
1778588564 59
1778588569 59
1778588574 59
1778588579 59
1778588584 59
1778588589 59
1778588594 59
1778588599 59
1778588604 59
1778588609 59
1778588614 59
1778588619 59
1778588624 59
1778588629 59
1778588634 59
1778588639 59
1778588644 59
1778588649 59
1778588654 64
```
</details>

---

