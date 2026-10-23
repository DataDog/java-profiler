---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:04:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 11 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 13 |
| Allocations | 207 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792764001 51
1792764006 51
1792764011 51
1792764016 51
1792764021 51
1792764026 51
1792764031 64
1792764036 64
1792764041 64
1792764046 64
1792764051 64
1792764056 64
1792764061 64
1792764066 64
1792764071 64
1792764076 64
1792764081 64
1792764086 64
1792764091 64
1792764096 64
```
</details>

---

