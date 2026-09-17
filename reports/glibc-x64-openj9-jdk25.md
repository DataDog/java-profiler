---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 05:57:23 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 31-66 cores)</summary>

```
1789638800 47
1789638805 47
1789638810 47
1789638815 47
1789638820 47
1789638825 64
1789638830 64
1789638835 64
1789638840 64
1789638845 66
1789638850 66
1789638855 31
1789638860 31
1789638865 31
1789638870 31
1789638875 31
1789638880 31
1789638885 31
1789638890 31
1789638895 31
```
</details>

---

