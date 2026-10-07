---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 10:47:23 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 74-82 cores)</summary>

```
1791384118 82
1791384123 82
1791384128 74
1791384133 74
1791384138 74
1791384143 74
1791384148 74
1791384153 78
1791384158 78
1791384163 78
1791384168 78
1791384173 78
1791384178 78
1791384183 78
1791384188 78
1791384193 78
1791384198 78
1791384203 78
1791384208 78
1791384213 78
```
</details>

---

