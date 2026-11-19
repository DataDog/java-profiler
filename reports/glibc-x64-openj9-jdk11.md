---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:14:20 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795108192 87
1795108197 87
1795108202 87
1795108207 87
1795108212 87
1795108217 87
1795108222 87
1795108227 87
1795108232 87
1795108237 85
1795108242 85
1795108247 85
1795108252 85
1795108257 85
1795108262 85
1795108267 85
1795108272 85
1795108277 87
1795108282 87
1795108287 87
```
</details>

---

