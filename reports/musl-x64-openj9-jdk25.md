---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 22.77/sec |
| Health Score | 1423% |
| Threads | 11 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 32.90/sec |
| Health Score | 2056% |
| Threads | 13 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (5 unique values: 68-76 cores)</summary>

```
1769526897 70
1769526902 70
1769526907 70
1769526912 68
1769526917 68
1769526922 71
1769526927 71
1769526932 71
1769526937 71
1769526942 71
1769526947 71
1769526952 71
1769526957 71
1769526962 71
1769526967 71
1769526972 71
1769526977 71
1769526982 71
1769526987 71
1769526992 74
```
</details>

---

