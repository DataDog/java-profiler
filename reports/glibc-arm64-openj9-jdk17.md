---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:55:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 11 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794484171 36
1794484176 36
1794484181 36
1794484186 36
1794484191 36
1794484196 36
1794484201 36
1794484206 36
1794484211 36
1794484216 36
1794484221 36
1794484226 36
1794484231 48
1794484236 48
1794484241 48
1794484246 48
1794484251 48
1794484256 48
1794484261 48
1794484266 48
```
</details>

---

