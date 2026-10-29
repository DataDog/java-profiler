---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:50:45 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 910 |
| Sample Rate | 15.17/sec |
| Health Score | 948% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288596 48
1793288601 48
1793288606 48
1793288611 48
1793288616 48
1793288621 48
1793288626 48
1793288631 48
1793288636 48
1793288641 48
1793288646 48
1793288651 48
1793288656 48
1793288661 48
1793288666 48
1793288671 48
1793288676 48
1793288681 48
1793288686 48
1793288691 48
```
</details>

---

