---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-30 09:25:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 81-96 cores)</summary>

```
1777555204 81
1777555209 81
1777555214 81
1777555219 81
1777555224 81
1777555229 81
1777555234 86
1777555239 86
1777555244 86
1777555249 91
1777555254 91
1777555259 96
1777555264 96
1777555269 96
1777555274 96
1777555279 96
1777555284 96
1777555289 96
1777555294 96
1777555299 96
```
</details>

---

