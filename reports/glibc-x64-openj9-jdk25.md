---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:11:46 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1795691234 59
1795691239 57
1795691244 57
1795691249 57
1795691254 57
1795691259 57
1795691264 57
1795691269 55
1795691274 55
1795691279 55
1795691284 55
1795691289 55
1795691294 55
1795691299 55
1795691304 55
1795691309 55
1795691314 55
1795691319 55
1795691324 55
1795691329 55
```
</details>

---

