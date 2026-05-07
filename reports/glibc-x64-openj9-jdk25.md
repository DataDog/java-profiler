---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:44:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 12 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 62-67 cores)</summary>

```
1778175594 67
1778175599 67
1778175604 62
1778175609 62
1778175614 62
1778175619 62
1778175624 62
1778175629 62
1778175634 62
1778175639 62
1778175644 62
1778175649 62
1778175654 62
1778175659 62
1778175664 62
1778175669 62
1778175674 67
1778175679 67
1778175684 67
1778175689 67
```
</details>

---

