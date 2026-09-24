---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 00:59:19 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 60-67 cores)</summary>

```
1790225619 62
1790225624 62
1790225629 62
1790225634 60
1790225639 60
1790225644 60
1790225649 60
1790225654 60
1790225659 60
1790225664 60
1790225669 60
1790225674 60
1790225679 60
1790225684 66
1790225689 66
1790225694 66
1790225699 66
1790225704 66
1790225709 67
1790225714 67
```
</details>

---

