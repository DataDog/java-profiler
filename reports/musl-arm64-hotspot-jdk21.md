---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:52:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795013135 48
1795013140 48
1795013145 48
1795013150 48
1795013155 48
1795013160 48
1795013166 48
1795013171 48
1795013176 48
1795013181 48
1795013186 48
1795013191 59
1795013196 59
1795013201 59
1795013206 59
1795013211 59
1795013216 59
1795013221 59
1795013226 59
1795013231 59
```
</details>

---

