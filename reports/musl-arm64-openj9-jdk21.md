---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-20 07:04:05 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 29-29 cores)</summary>

```
1795175976 29
1795175981 29
1795175986 29
1795175991 29
1795175996 29
1795176001 29
1795176006 29
1795176011 29
1795176016 29
1795176021 29
1795176026 29
1795176031 29
1795176036 29
1795176041 29
1795176046 29
1795176051 29
1795176056 29
1795176061 29
1795176066 29
1795176071 29
```
</details>

---

