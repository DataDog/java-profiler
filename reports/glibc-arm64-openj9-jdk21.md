---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 9 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1793800139 43
1793800144 43
1793800149 43
1793800154 43
1793800159 43
1793800164 43
1793800169 43
1793800174 43
1793800179 43
1793800184 43
1793800189 43
1793800194 43
1793800199 43
1793800204 43
1793800209 43
1793800214 43
1793800219 43
1793800224 41
1793800229 41
1793800234 41
```
</details>

---

