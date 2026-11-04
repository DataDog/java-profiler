---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:45 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793800144 43
1793800149 43
1793800154 43
1793800159 43
1793800164 43
1793800169 48
1793800174 48
1793800179 48
1793800184 48
1793800189 48
1793800194 48
1793800199 48
1793800204 48
1793800209 48
1793800214 48
1793800219 48
1793800224 48
1793800229 48
1793800234 48
1793800239 48
```
</details>

---

