---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 00:57:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1788065554 23
1788065559 23
1788065565 23
1788065570 23
1788065575 23
1788065580 23
1788065585 23
1788065590 23
1788065595 23
1788065600 23
1788065605 23
1788065610 23
1788065615 23
1788065620 23
1788065625 23
1788065630 23
1788065635 28
1788065640 28
1788065645 28
1788065650 28
```
</details>

---

