---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 56-64 cores)</summary>

```
1794914886 56
1794914891 56
1794914896 56
1794914901 56
1794914906 56
1794914911 56
1794914916 56
1794914921 56
1794914926 64
1794914931 64
1794914936 64
1794914941 64
1794914946 64
1794914951 64
1794914956 64
1794914961 64
1794914966 64
1794914971 64
1794914976 64
1794914981 64
```
</details>

---

