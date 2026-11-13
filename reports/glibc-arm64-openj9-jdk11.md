---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:40:54 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (5 unique values: 40-45 cores)</summary>

```
1794573226 43
1794573231 43
1794573236 41
1794573241 41
1794573246 41
1794573251 41
1794573256 41
1794573261 41
1794573266 41
1794573271 41
1794573276 40
1794573281 40
1794573286 43
1794573291 43
1794573296 40
1794573301 40
1794573306 40
1794573311 40
1794573316 40
1794573321 42
```
</details>

---

