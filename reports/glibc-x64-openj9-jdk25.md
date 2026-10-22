---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 16:56:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 80-91 cores)</summary>

```
1792702226 86
1792702231 86
1792702236 86
1792702241 86
1792702246 86
1792702251 86
1792702256 86
1792702261 86
1792702266 91
1792702271 91
1792702276 91
1792702281 91
1792702286 91
1792702291 91
1792702296 91
1792702301 91
1792702306 82
1792702311 82
1792702316 82
1792702321 82
```
</details>

---

