---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 11:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1056 |
| Sample Rate | 17.60/sec |
| Health Score | 1100% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 77-88 cores)</summary>

```
1778167226 77
1778167231 82
1778167236 82
1778167241 85
1778167246 85
1778167251 85
1778167256 85
1778167261 86
1778167266 86
1778167271 86
1778167276 86
1778167281 86
1778167286 86
1778167291 86
1778167296 86
1778167301 86
1778167306 86
1778167311 86
1778167316 86
1778167321 86
```
</details>

---

