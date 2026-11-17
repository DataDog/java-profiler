---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 07:23:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1794917976 32
1794917981 32
1794917986 32
1794917991 32
1794917996 32
1794918001 32
1794918006 32
1794918011 32
1794918016 32
1794918021 32
1794918026 32
1794918031 32
1794918036 32
1794918041 52
1794918046 52
1794918051 32
1794918056 32
1794918061 32
1794918066 32
1794918071 32
```
</details>

---

