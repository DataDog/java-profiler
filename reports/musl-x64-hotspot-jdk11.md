---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:32:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 51-54 cores)</summary>

```
1793194169 53
1793194174 53
1793194179 53
1793194184 53
1793194189 53
1793194194 53
1793194199 53
1793194204 53
1793194209 53
1793194214 51
1793194219 51
1793194224 51
1793194229 51
1793194234 51
1793194239 51
1793194244 51
1793194249 54
1793194254 54
1793194259 54
1793194264 54
```
</details>

---

