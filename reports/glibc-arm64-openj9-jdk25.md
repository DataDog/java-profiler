---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 20:59:10 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1793148932 14
1793148937 14
1793148942 14
1793148947 14
1793148952 14
1793148957 14
1793148962 14
1793148967 14
1793148972 14
1793148977 14
1793148982 14
1793148987 14
1793148992 14
1793148997 14
1793149002 34
1793149007 34
1793149012 34
1793149017 34
1793149022 34
1793149027 34
```
</details>

---

