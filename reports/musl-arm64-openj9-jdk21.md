---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 01:04:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 13 |
| Allocations | 190 |

<details>
<summary>CPU Timeline (2 unique values: 11-13 cores)</summary>

```
1791953951 13
1791953956 13
1791953961 13
1791953966 13
1791953971 13
1791953976 13
1791953981 13
1791953986 13
1791953991 13
1791953996 13
1791954001 13
1791954006 13
1791954011 13
1791954016 13
1791954021 13
1791954026 13
1791954031 13
1791954036 13
1791954041 11
1791954046 11
```
</details>

---

