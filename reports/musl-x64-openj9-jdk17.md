---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-04 13:27:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (6 unique values: 44-72 cores)</summary>

```
1770229191 68
1770229196 68
1770229201 68
1770229206 72
1770229211 72
1770229216 44
1770229221 44
1770229226 44
1770229231 44
1770229236 44
1770229241 44
1770229246 47
1770229251 47
1770229256 47
1770229261 47
1770229266 47
1770229271 47
1770229276 47
1770229281 47
1770229286 49
```
</details>

---

