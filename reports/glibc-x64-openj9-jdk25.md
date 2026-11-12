---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794508193 92
1794508198 92
1794508203 92
1794508208 92
1794508213 92
1794508218 92
1794508223 92
1794508228 92
1794508233 92
1794508238 92
1794508243 92
1794508248 92
1794508253 92
1794508258 92
1794508263 92
1794508268 92
1794508273 92
1794508278 94
1794508283 94
1794508288 94
```
</details>

---

