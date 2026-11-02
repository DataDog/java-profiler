---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 08:00:03 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 8 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 46-60 cores)</summary>

```
1793624139 60
1793624144 60
1793624149 48
1793624154 48
1793624159 48
1793624164 48
1793624169 48
1793624174 48
1793624179 48
1793624184 48
1793624189 48
1793624194 48
1793624199 48
1793624204 48
1793624209 48
1793624214 48
1793624219 48
1793624224 48
1793624229 48
1793624234 48
```
</details>

---

