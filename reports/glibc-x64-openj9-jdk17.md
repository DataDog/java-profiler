---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 11:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (5 unique values: 68-76 cores)</summary>

```
1778167223 74
1778167228 74
1778167233 74
1778167238 74
1778167243 74
1778167248 76
1778167253 76
1778167258 76
1778167263 73
1778167268 73
1778167273 73
1778167278 75
1778167283 75
1778167288 75
1778167293 75
1778167298 73
1778167303 73
1778167308 73
1778167313 73
1778167318 73
```
</details>

---

