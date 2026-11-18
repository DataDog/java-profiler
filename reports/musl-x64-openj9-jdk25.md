---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 00:06:55 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 11-56 cores)</summary>

```
1794978131 11
1794978136 11
1794978142 11
1794978147 11
1794978152 11
1794978157 56
1794978162 56
1794978167 56
1794978172 56
1794978177 56
1794978182 56
1794978187 56
1794978192 56
1794978197 56
1794978202 56
1794978207 56
1794978212 56
1794978217 56
1794978222 56
1794978227 56
```
</details>

---

