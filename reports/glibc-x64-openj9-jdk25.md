---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 17:32:19 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 43-65 cores)</summary>

```
1777325172 43
1777325177 63
1777325182 63
1777325187 65
1777325192 65
1777325197 65
1777325202 65
1777325207 65
1777325212 65
1777325217 65
1777325222 65
1777325227 65
1777325232 65
1777325237 65
1777325242 65
1777325247 65
1777325252 65
1777325257 65
1777325262 65
1777325267 65
```
</details>

---

