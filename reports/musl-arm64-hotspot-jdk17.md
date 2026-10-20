---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:11:02 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792505026 51
1792505031 51
1792505036 51
1792505041 51
1792505046 51
1792505051 51
1792505056 51
1792505061 51
1792505066 51
1792505071 51
1792505076 51
1792505081 51
1792505086 51
1792505091 51
1792505096 51
1792505101 51
1792505106 51
1792505111 51
1792505117 51
1792505122 46
```
</details>

---

