---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:54:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
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
1793800244 48
1793800249 48
1793800254 48
1793800259 48
1793800264 48
1793800269 48
```
</details>

---

