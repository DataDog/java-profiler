---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-24 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 13 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1792831131 35
1792831136 35
1792831141 35
1792831146 35
1792831151 35
1792831156 35
1792831161 35
1792831166 35
1792831171 35
1792831176 35
1792831181 35
1792831186 35
1792831191 35
1792831196 40
1792831201 40
1792831206 40
1792831211 40
1792831216 40
1792831221 40
1792831226 40
```
</details>

---

