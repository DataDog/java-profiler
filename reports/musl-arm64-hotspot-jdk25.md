---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:00:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 15-28 cores)</summary>

```
1794354916 28
1794354921 28
1794354926 28
1794354931 28
1794354936 28
1794354941 28
1794354946 28
1794354951 28
1794354956 28
1794354961 28
1794354966 28
1794354971 28
1794354976 28
1794354981 28
1794354986 28
1794354991 28
1794354996 28
1794355001 28
1794355006 28
1794355011 28
```
</details>

---

