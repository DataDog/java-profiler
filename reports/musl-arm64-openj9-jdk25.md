---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:00:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 14 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (5 unique values: 46-64 cores)</summary>

```
1794354921 46
1794354926 46
1794354931 46
1794354936 59
1794354941 59
1794354946 64
1794354951 64
1794354956 64
1794354961 64
1794354966 47
1794354971 47
1794354976 47
1794354981 47
1794354986 47
1794354991 47
1794354996 47
1794355001 64
1794355006 64
1794355011 52
1794355016 52
```
</details>

---

