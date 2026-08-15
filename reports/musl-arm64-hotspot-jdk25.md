---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-15 05:47:15 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786786991 46
1786786996 46
1786787001 46
1786787006 46
1786787011 46
1786787016 46
1786787021 46
1786787026 46
1786787031 46
1786787036 48
1786787041 48
1786787046 48
1786787051 48
1786787056 48
1786787061 48
1786787066 48
1786787071 48
1786787076 48
1786787081 48
1786787086 48
```
</details>

---

