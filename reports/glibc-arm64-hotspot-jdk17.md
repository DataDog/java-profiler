---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 08:54:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1793800150 41
1793800155 41
1793800160 41
1793800165 41
1793800170 41
1793800175 41
1793800180 46
1793800185 46
1793800190 46
1793800195 46
1793800200 46
1793800205 46
1793800210 46
1793800215 46
1793800220 46
1793800225 46
1793800230 46
1793800235 46
1793800240 46
1793800245 46
```
</details>

---

