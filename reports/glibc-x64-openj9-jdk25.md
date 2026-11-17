---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 08:01:56 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 82-90 cores)</summary>

```
1794920168 90
1794920173 90
1794920178 88
1794920183 88
1794920188 88
1794920193 88
1794920198 88
1794920203 88
1794920208 86
1794920213 86
1794920218 86
1794920223 86
1794920228 86
1794920233 86
1794920238 86
1794920243 86
1794920248 86
1794920253 86
1794920258 86
1794920263 86
```
</details>

---

