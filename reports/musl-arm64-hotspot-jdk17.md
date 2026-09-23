---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 11:28:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (4 unique values: 35-48 cores)</summary>

```
1790176996 48
1790177001 48
1790177006 48
1790177011 48
1790177016 48
1790177021 48
1790177026 48
1790177031 48
1790177036 48
1790177041 48
1790177046 48
1790177051 48
1790177056 48
1790177061 48
1790177066 48
1790177071 48
1790177076 48
1790177081 43
1790177086 43
1790177091 43
```
</details>

---

