---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 12 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 33-46 cores)</summary>

```
1794917975 33
1794917980 33
1794917986 33
1794917991 33
1794917996 33
1794918001 33
1794918006 33
1794918011 33
1794918016 33
1794918021 33
1794918026 33
1794918031 33
1794918036 33
1794918041 33
1794918046 33
1794918051 33
1794918056 46
1794918061 46
1794918066 46
1794918071 46
```
</details>

---

