---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 00:59:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 18-40 cores)</summary>

```
1790225621 18
1790225626 18
1790225631 18
1790225636 18
1790225641 18
1790225646 24
1790225651 24
1790225656 26
1790225661 26
1790225666 26
1790225671 26
1790225676 28
1790225681 28
1790225686 28
1790225691 28
1790225696 28
1790225701 28
1790225706 28
1790225711 28
1790225716 40
```
</details>

---

