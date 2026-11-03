---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 23-48 cores)</summary>

```
1793742198 48
1793742203 43
1793742208 43
1793742213 43
1793742218 43
1793742223 23
1793742228 23
1793742233 23
1793742238 23
1793742243 23
1793742248 23
1793742253 28
1793742258 28
1793742263 28
1793742268 28
1793742273 28
1793742278 28
1793742283 28
1793742288 28
1793742293 28
```
</details>

---

