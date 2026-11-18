---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 00:06:53 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1794978143 65
1794978148 65
1794978153 65
1794978158 65
1794978163 65
1794978168 65
1794978173 67
1794978178 67
1794978183 67
1794978188 67
1794978193 67
1794978198 67
1794978203 67
1794978208 67
1794978213 67
1794978218 67
1794978223 67
1794978228 67
1794978233 67
1794978238 67
```
</details>

---

