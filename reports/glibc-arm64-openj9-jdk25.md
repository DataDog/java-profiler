---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 16:13:23 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 14 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794776945 38
1794776950 38
1794776955 38
1794776960 38
1794776965 38
1794776970 38
1794776975 38
1794776980 38
1794776985 38
1794776990 38
1794776995 38
1794777000 38
1794777005 38
1794777010 38
1794777015 38
1794777020 38
1794777025 38
1794777030 51
1794777035 51
1794777040 51
```
</details>

---

