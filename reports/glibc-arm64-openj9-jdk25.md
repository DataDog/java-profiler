---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 22:03:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 10 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794020220 40
1794020225 40
1794020230 40
1794020235 40
1794020240 40
1794020245 40
1794020250 40
1794020255 40
1794020260 40
1794020265 40
1794020270 40
1794020275 40
1794020280 40
1794020285 40
1794020290 40
1794020295 40
1794020300 40
1794020305 40
1794020310 40
1794020315 40
```
</details>

---

