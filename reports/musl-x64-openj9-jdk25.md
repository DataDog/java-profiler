---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 11:59:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 10 |
| Allocations | 435 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 78-88 cores)</summary>

```
1794243144 86
1794243149 86
1794243154 86
1794243159 86
1794243164 86
1794243169 88
1794243174 88
1794243179 82
1794243184 82
1794243189 82
1794243194 80
1794243199 80
1794243204 80
1794243209 80
1794243214 80
1794243219 80
1794243224 80
1794243229 80
1794243234 80
1794243239 80
```
</details>

---

