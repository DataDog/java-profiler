---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:00:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (6 unique values: 63-83 cores)</summary>

```
1795452894 65
1795452899 65
1795452904 63
1795452909 63
1795452914 63
1795452919 63
1795452924 63
1795452929 63
1795452934 63
1795452939 63
1795452944 63
1795452949 74
1795452954 74
1795452959 74
1795452964 74
1795452969 74
1795452974 74
1795452979 74
1795452984 74
1795452989 72
```
</details>

---

