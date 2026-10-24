---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-24 05:16:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1792833183 77
1792833188 77
1792833193 77
1792833198 77
1792833203 75
1792833208 75
1792833213 75
1792833218 75
1792833223 75
1792833228 75
1792833233 75
1792833238 77
1792833243 77
1792833248 79
1792833253 79
1792833258 79
1792833264 79
1792833269 79
1792833274 79
1792833279 79
```
</details>

---

