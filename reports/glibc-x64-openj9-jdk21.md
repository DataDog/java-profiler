---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 06:31:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 10 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 51-70 cores)</summary>

```
1790850481 51
1790850486 63
1790850491 63
1790850496 63
1790850501 63
1790850506 63
1790850511 65
1790850516 65
1790850521 65
1790850526 65
1790850531 65
1790850536 70
1790850541 70
1790850546 70
1790850551 70
1790850556 70
1790850561 70
1790850566 70
1790850571 70
1790850576 70
```
</details>

---

