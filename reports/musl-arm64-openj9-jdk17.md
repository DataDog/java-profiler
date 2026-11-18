---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:52:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1795013153 41
1795013158 41
1795013163 41
1795013168 41
1795013173 59
1795013178 59
1795013183 46
1795013188 46
1795013193 51
1795013198 51
1795013203 51
1795013208 51
1795013213 51
1795013218 51
1795013223 51
1795013228 51
1795013233 51
1795013238 51
1795013243 51
1795013248 51
```
</details>

---

