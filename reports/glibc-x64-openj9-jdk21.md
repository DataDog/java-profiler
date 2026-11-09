---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 16:19:00 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 63-86 cores)</summary>

```
1794258886 63
1794258891 65
1794258896 65
1794258901 63
1794258906 63
1794258911 63
1794258916 65
1794258921 65
1794258926 65
1794258931 65
1794258936 70
1794258941 70
1794258946 70
1794258951 70
1794258956 70
1794258961 70
1794258966 70
1794258971 70
1794258976 70
1794258981 70
```
</details>

---

