---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:38:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 10 |
| Allocations | 120 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793367176 48
1793367181 48
1793367186 43
1793367191 43
1793367196 43
1793367201 43
1793367206 43
1793367211 43
1793367216 43
1793367221 43
1793367226 43
1793367231 43
1793367236 48
1793367242 48
1793367247 48
1793367252 48
1793367257 48
1793367262 48
1793367267 48
1793367272 48
```
</details>

---

