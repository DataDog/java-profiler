---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-02 15:17:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770063118 32
1770063123 32
1770063128 32
1770063133 32
1770063138 32
1770063143 32
1770063148 32
1770063153 32
1770063158 32
1770063163 27
1770063168 27
1770063173 27
1770063178 27
1770063183 27
1770063188 27
1770063193 27
1770063198 27
1770063203 27
1770063208 27
1770063213 32
```
</details>

---

