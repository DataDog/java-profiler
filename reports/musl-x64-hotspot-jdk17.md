---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-29 11:09:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 60-66 cores)</summary>

```
1777475041 61
1777475046 61
1777475051 61
1777475056 61
1777475061 60
1777475066 60
1777475071 60
1777475076 60
1777475081 60
1777475086 60
1777475091 60
1777475096 60
1777475101 63
1777475106 63
1777475111 63
1777475116 63
1777475121 63
1777475126 63
1777475131 63
1777475136 63
```
</details>

---

