---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 01:04:05 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1791953941 77
1791953946 77
1791953951 79
1791953956 79
1791953961 81
1791953966 81
1791953971 81
1791953976 81
1791953981 81
1791953986 81
1791953991 81
1791953996 81
1791954001 81
1791954006 81
1791954011 81
1791954016 81
1791954021 81
1791954026 81
1791954031 81
1791954036 81
```
</details>

---

