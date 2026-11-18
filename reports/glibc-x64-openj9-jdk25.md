---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 00:06:53 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1794978163 87
1794978168 87
1794978173 87
1794978178 87
1794978183 87
1794978188 87
1794978193 87
1794978198 87
1794978203 87
1794978208 87
1794978213 87
1794978218 87
1794978223 87
1794978228 87
1794978233 96
1794978238 96
1794978243 96
1794978248 96
1794978253 96
1794978258 96
```
</details>

---

