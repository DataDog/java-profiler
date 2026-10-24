---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-24 04:44:31 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 14 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792831116 43
1792831121 43
1792831126 43
1792831131 43
1792831136 43
1792831141 43
1792831146 43
1792831151 43
1792831156 43
1792831161 43
1792831166 43
1792831171 43
1792831176 43
1792831181 43
1792831187 43
1792831192 43
1792831197 43
1792831202 43
1792831207 48
1792831212 48
```
</details>

---

