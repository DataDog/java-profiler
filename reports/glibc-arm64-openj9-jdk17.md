---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-02-02 12:55:22 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770054720 24
1770054725 24
1770054730 24
1770054735 24
1770054740 24
1770054745 24
1770054750 24
1770054755 24
1770054760 24
1770054765 24
1770054770 24
1770054775 24
1770054780 24
1770054785 24
1770054790 24
1770054795 24
1770054800 24
1770054805 24
1770054810 24
1770054815 24
```
</details>

---

