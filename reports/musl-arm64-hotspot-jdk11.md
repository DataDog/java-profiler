---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:08:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (5 unique values: 44-54 cores)</summary>

```
1792505011 53
1792505016 53
1792505021 53
1792505026 48
1792505031 48
1792505036 48
1792505041 54
1792505046 54
1792505051 44
1792505056 44
1792505061 44
1792505066 44
1792505071 44
1792505076 44
1792505081 44
1792505086 44
1792505091 44
1792505096 44
1792505101 44
1792505106 44
```
</details>

---

