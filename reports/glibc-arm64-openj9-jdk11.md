---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:37:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1793889110 42
1793889115 42
1793889121 42
1793889126 42
1793889131 43
1793889136 43
1793889141 43
1793889146 43
1793889151 43
1793889156 43
1793889161 48
1793889166 48
1793889171 45
1793889176 45
1793889181 45
1793889186 45
1793889191 45
1793889196 45
1793889201 45
1793889206 45
```
</details>

---

