---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:43:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1794487199 40
1794487204 40
1794487209 40
1794487214 40
1794487219 40
1794487224 40
1794487229 40
1794487234 40
1794487239 40
1794487244 40
1794487249 40
1794487254 40
1794487259 40
1794487264 40
1794487269 40
1794487274 40
1794487279 48
1794487284 48
1794487289 48
1794487294 48
```
</details>

---

