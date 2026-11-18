---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 00:06:55 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794978148 96
1794978153 96
1794978158 96
1794978163 96
1794978168 96
1794978173 96
1794978178 94
1794978183 94
1794978188 94
1794978193 94
1794978198 94
1794978203 96
1794978208 96
1794978213 96
1794978218 96
1794978223 96
1794978228 96
1794978233 96
1794978238 96
1794978243 96
```
</details>

---

