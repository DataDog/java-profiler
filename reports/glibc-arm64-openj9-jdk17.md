---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 10:05:14 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793023224 43
1793023229 43
1793023234 43
1793023239 43
1793023244 43
1793023249 48
1793023254 48
1793023259 48
1793023264 48
1793023269 48
1793023274 48
1793023279 48
1793023284 48
1793023289 48
1793023294 48
1793023299 48
1793023304 48
1793023309 48
1793023314 48
1793023319 48
```
</details>

---

