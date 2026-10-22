---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:35:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 23-32 cores)</summary>

```
1792675562 23
1792675567 23
1792675572 25
1792675577 25
1792675582 25
1792675587 25
1792675592 25
1792675597 25
1792675602 25
1792675607 25
1792675612 25
1792675617 25
1792675622 23
1792675627 23
1792675632 23
1792675637 30
1792675642 30
1792675647 30
1792675652 30
1792675657 30
```
</details>

---

