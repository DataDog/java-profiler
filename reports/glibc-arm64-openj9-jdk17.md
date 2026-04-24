---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:31:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777033587 59
1777033592 59
1777033597 59
1777033602 59
1777033607 59
1777033612 59
1777033617 59
1777033622 59
1777033627 59
1777033632 59
1777033637 59
1777033642 59
1777033647 59
1777033652 59
1777033657 59
1777033662 59
1777033667 59
1777033672 64
1777033677 64
1777033682 64
```
</details>

---

