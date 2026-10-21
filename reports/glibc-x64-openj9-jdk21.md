---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 06:29:48 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 70-88 cores)</summary>

```
1792578328 88
1792578333 88
1792578338 88
1792578343 88
1792578348 80
1792578353 80
1792578358 80
1792578363 80
1792578368 80
1792578373 80
1792578378 80
1792578383 80
1792578388 80
1792578393 80
1792578398 80
1792578403 80
1792578408 80
1792578413 80
1792578418 70
1792578423 70
```
</details>

---

