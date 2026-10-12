---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 9 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (6 unique values: 41-47 cores)</summary>

```
1791794214 47
1791794219 47
1791794224 44
1791794229 44
1791794234 44
1791794239 44
1791794244 44
1791794249 44
1791794254 45
1791794259 45
1791794264 45
1791794269 45
1791794274 45
1791794279 45
1791794284 43
1791794289 43
1791794294 42
1791794299 42
1791794304 42
1791794309 42
```
</details>

---

