---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 00:59:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 297 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (6 unique values: 78-90 cores)</summary>

```
1790225616 80
1790225621 80
1790225626 80
1790225631 80
1790225636 80
1790225641 80
1790225646 80
1790225651 82
1790225656 82
1790225661 88
1790225666 88
1790225671 88
1790225676 88
1790225681 88
1790225686 88
1790225691 90
1790225696 90
1790225701 78
1790225706 78
1790225711 78
```
</details>

---

