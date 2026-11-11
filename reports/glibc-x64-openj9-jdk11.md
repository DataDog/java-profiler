---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:47:14 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 73-76 cores)</summary>

```
1794408158 76
1794408163 76
1794408168 76
1794408173 76
1794408178 76
1794408183 76
1794408188 76
1794408193 76
1794408198 76
1794408203 76
1794408208 73
1794408213 73
1794408218 73
1794408223 73
1794408228 73
1794408233 73
1794408238 73
1794408243 73
1794408248 73
1794408253 73
```
</details>

---

