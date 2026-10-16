---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 11:26:16 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792164011 48
1792164016 48
1792164021 48
1792164026 48
1792164031 48
1792164036 48
1792164041 48
1792164046 48
1792164051 48
1792164056 48
1792164061 48
1792164066 48
1792164071 48
1792164076 48
1792164081 48
1792164086 48
1792164091 43
1792164096 43
1792164101 43
1792164106 43
```
</details>

---

