---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 10:47:47 EDT

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1791988932 48
1791988937 48
1791988942 48
1791988947 48
1791988952 48
1791988957 44
1791988962 44
1791988967 44
1791988972 44
1791988977 44
1791988982 44
1791988987 44
1791988992 44
1791988997 44
1791989002 44
1791989007 44
1791989012 44
1791989017 44
1791989022 44
1791989028 44
```
</details>

---

