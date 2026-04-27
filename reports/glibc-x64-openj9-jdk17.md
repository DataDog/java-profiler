---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 44-59 cores)</summary>

```
1777321208 59
1777321213 59
1777321218 59
1777321223 59
1777321228 59
1777321233 59
1777321238 59
1777321243 59
1777321248 59
1777321253 59
1777321258 59
1777321263 59
1777321268 59
1777321273 59
1777321278 59
1777321283 59
1777321288 59
1777321293 44
1777321299 44
1777321304 44
```
</details>

---

