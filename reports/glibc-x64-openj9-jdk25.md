---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 05:55:33 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 61-84 cores)</summary>

```
1792576256 84
1792576261 84
1792576266 84
1792576271 82
1792576276 82
1792576281 61
1792576286 61
1792576291 61
1792576296 61
1792576301 61
1792576306 61
1792576311 61
1792576316 61
1792576321 61
1792576326 63
1792576331 63
1792576336 63
1792576341 63
1792576346 63
1792576351 63
```
</details>

---

