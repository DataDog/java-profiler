---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:34:17 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1790094247 22
1790094252 22
1790094257 22
1790094262 22
1790094267 22
1790094272 22
1790094277 22
1790094282 22
1790094287 22
1790094292 22
1790094297 22
1790094302 22
1790094307 20
1790094312 20
1790094317 20
1790094322 20
1790094327 20
1790094332 20
1790094337 22
1790094342 22
```
</details>

---

