---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 06:46:59 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 70-94 cores)</summary>

```
1792665768 72
1792665773 72
1792665778 72
1792665783 72
1792665788 72
1792665793 72
1792665798 72
1792665803 72
1792665808 72
1792665813 70
1792665818 70
1792665823 70
1792665828 70
1792665833 70
1792665838 70
1792665843 70
1792665848 70
1792665853 73
1792665858 73
1792665863 73
```
</details>

---

