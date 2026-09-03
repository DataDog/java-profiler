---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 12:03:40 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 9 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788451189 62
1788451194 62
1788451199 62
1788451204 62
1788451209 62
1788451214 62
1788451219 62
1788451224 62
1788451229 62
1788451234 62
1788451239 62
1788451244 62
1788451249 62
1788451254 62
1788451259 62
1788451264 62
1788451269 62
1788451274 64
1788451279 64
1788451284 64
```
</details>

---

