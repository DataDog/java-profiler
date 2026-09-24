---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 14:06:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790272921 50
1790272926 50
1790272931 50
1790272936 50
1790272941 50
1790272946 50
1790272951 50
1790272956 50
1790272961 50
1790272966 50
1790272971 50
1790272976 50
1790272981 50
1790272986 50
1790272991 50
1790272996 50
1790273001 50
1790273006 50
1790273011 50
1790273016 50
```
</details>

---

