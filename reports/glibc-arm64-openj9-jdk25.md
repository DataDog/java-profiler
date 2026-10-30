---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:28:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793355889 48
1793355894 48
1793355899 48
1793355904 48
1793355909 48
1793355914 48
1793355919 48
1793355924 48
1793355929 48
1793355934 48
1793355939 48
1793355944 48
1793355949 48
1793355954 48
1793355959 48
1793355964 48
1793355969 48
1793355974 48
1793355979 48
1793355984 48
```
</details>

---

