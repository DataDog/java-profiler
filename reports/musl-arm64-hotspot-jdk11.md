---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 11:26:16 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 14 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 53-54 cores)</summary>

```
1792164040 54
1792164045 54
1792164050 54
1792164056 54
1792164061 54
1792164066 54
1792164071 54
1792164076 54
1792164081 54
1792164086 53
1792164091 53
1792164096 53
1792164101 53
1792164106 53
1792164111 53
1792164116 53
1792164121 53
1792164126 53
1792164131 53
1792164136 53
```
</details>

---

