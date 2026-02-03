---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 12:32:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1770139455 26
1770139460 26
1770139465 26
1770139470 26
1770139475 26
1770139480 26
1770139485 26
1770139490 26
1770139495 26
1770139500 26
1770139505 30
1770139510 30
1770139515 30
1770139520 30
1770139525 28
1770139530 28
1770139535 28
1770139540 28
1770139545 30
1770139550 30
```
</details>

---

