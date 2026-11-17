---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 86-91 cores)</summary>

```
1794917961 91
1794917966 91
1794917971 91
1794917976 91
1794917981 91
1794917986 91
1794917991 91
1794917996 91
1794918001 91
1794918006 88
1794918011 88
1794918016 88
1794918021 88
1794918026 88
1794918031 88
1794918036 88
1794918041 88
1794918046 88
1794918051 86
1794918056 86
```
</details>

---

