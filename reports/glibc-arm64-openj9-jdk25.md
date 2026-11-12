---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 11:57:02 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (6 unique values: 42-48 cores)</summary>

```
1794502143 48
1794502148 48
1794502153 48
1794502158 48
1794502163 48
1794502168 48
1794502173 48
1794502178 48
1794502183 48
1794502188 48
1794502193 48
1794502198 48
1794502203 48
1794502208 47
1794502213 47
1794502218 47
1794502223 47
1794502228 47
1794502233 47
1794502238 45
```
</details>

---

