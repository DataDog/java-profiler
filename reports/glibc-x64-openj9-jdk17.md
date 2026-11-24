---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 60-78 cores)</summary>

```
1795517176 60
1795517181 60
1795517186 60
1795517191 60
1795517196 60
1795517201 60
1795517206 60
1795517211 62
1795517216 62
1795517221 62
1795517226 62
1795517231 62
1795517236 62
1795517241 62
1795517246 62
1795517251 70
1795517256 70
1795517261 70
1795517266 70
1795517271 78
```
</details>

---

