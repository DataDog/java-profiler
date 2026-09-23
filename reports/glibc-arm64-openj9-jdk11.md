---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:37 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790172194 38
1790172199 38
1790172204 38
1790172209 38
1790172214 43
1790172219 43
1790172224 43
1790172229 43
1790172234 43
1790172239 43
1790172244 43
1790172249 43
1790172254 43
1790172259 43
1790172264 43
1790172269 43
1790172274 43
1790172279 43
1790172284 43
1790172289 43
```
</details>

---

