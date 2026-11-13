---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:25:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 67-78 cores)</summary>

```
1794583236 76
1794583241 76
1794583246 76
1794583251 76
1794583256 76
1794583261 78
1794583266 78
1794583271 73
1794583276 73
1794583281 73
1794583286 69
1794583291 69
1794583296 69
1794583301 69
1794583306 69
1794583311 69
1794583317 69
1794583322 69
1794583327 69
1794583332 69
```
</details>

---

