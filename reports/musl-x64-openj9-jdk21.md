---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 15:37:59 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 955 |
| Sample Rate | 15.92/sec |
| Health Score | 995% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1795465936 84
1795465941 87
1795465946 87
1795465951 87
1795465956 87
1795465961 87
1795465966 87
1795465971 87
1795465976 87
1795465981 87
1795465986 87
1795465991 87
1795465996 87
1795466001 87
1795466006 87
1795466012 87
1795466017 87
1795466022 82
1795466027 82
1795466032 82
```
</details>

---

