---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:47:26 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 87-89 cores)</summary>

```
1793644971 87
1793644976 87
1793644981 87
1793644986 87
1793644991 87
1793644996 87
1793645001 87
1793645006 87
1793645011 87
1793645016 87
1793645021 87
1793645026 87
1793645031 87
1793645036 89
1793645041 89
1793645046 89
1793645051 89
1793645056 89
1793645061 89
1793645066 89
```
</details>

---

