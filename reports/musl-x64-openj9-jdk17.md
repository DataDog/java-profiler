---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:12:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1770134700 28
1770134705 28
1770134710 28
1770134715 28
1770134720 28
1770134726 28
1770134731 28
1770134736 28
1770134741 28
1770134746 28
1770134751 23
1770134756 23
1770134761 23
1770134766 23
1770134771 23
1770134776 23
1770134781 23
1770134786 23
1770134791 23
1770134796 23
```
</details>

---

