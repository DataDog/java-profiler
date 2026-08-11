---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 12:25:48 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 37-46 cores)</summary>

```
1786465143 42
1786465148 42
1786465153 37
1786465158 37
1786465163 37
1786465168 37
1786465173 37
1786465178 37
1786465183 37
1786465188 37
1786465193 46
1786465198 46
1786465203 46
1786465208 46
1786465213 46
1786465218 46
1786465223 46
1786465228 46
1786465233 46
1786465238 46
```
</details>

---

