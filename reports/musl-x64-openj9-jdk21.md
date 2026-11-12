---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:55:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 59-80 cores)</summary>

```
1794487796 61
1794487801 61
1794487806 61
1794487811 63
1794487816 63
1794487821 63
1794487826 63
1794487831 61
1794487836 61
1794487841 61
1794487846 61
1794487851 59
1794487856 59
1794487861 61
1794487867 61
1794487872 61
1794487877 61
1794487882 61
1794487887 61
1794487892 61
```
</details>

---

