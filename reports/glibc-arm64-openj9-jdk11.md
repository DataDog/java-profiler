---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 16:24:54 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793827197 48
1793827202 48
1793827207 48
1793827212 48
1793827217 48
1793827222 48
1793827227 48
1793827232 48
1793827237 48
1793827242 48
1793827247 48
1793827252 48
1793827257 48
1793827262 43
1793827267 43
1793827272 43
1793827277 43
1793827282 43
1793827287 43
1793827292 43
```
</details>

---

