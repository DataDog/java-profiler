---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 09:57:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1777384234 27
1777384239 27
1777384244 27
1777384249 27
1777384254 27
1777384259 27
1777384264 27
1777384269 27
1777384274 22
1777384279 22
1777384284 22
1777384289 22
1777384294 22
1777384299 22
1777384304 22
1777384309 22
1777384314 22
1777384319 22
1777384324 22
1777384329 22
```
</details>

---

