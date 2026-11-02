---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 13:47:25 EST

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 12-47 cores)</summary>

```
1793644981 12
1793644986 13
1793644991 13
1793644996 13
1793645001 13
1793645006 13
1793645011 13
1793645016 13
1793645021 13
1793645026 47
1793645031 47
1793645036 47
1793645041 47
1793645046 47
1793645051 47
1793645056 47
1793645061 47
1793645066 47
1793645071 47
1793645076 47
```
</details>

---

