---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 17.87/sec |
| Health Score | 1117% |
| Threads | 10 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 24.43/sec |
| Health Score | 1527% |
| Threads | 12 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 72-77 cores)</summary>

```
1769525204 77
1769525210 77
1769525215 77
1769525220 77
1769525225 77
1769525230 72
1769525235 72
1769525240 72
1769525245 72
1769525250 72
1769525255 72
1769525260 72
1769525265 72
1769525270 72
1769525275 72
1769525280 72
1769525285 72
1769525290 72
1769525295 72
1769525300 72
```
</details>

---

