---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:54:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 41-63 cores)</summary>

```
1793800150 41
1793800155 41
1793800160 41
1793800165 41
1793800170 41
1793800175 41
1793800180 41
1793800185 41
1793800190 41
1793800195 41
1793800200 41
1793800205 41
1793800210 41
1793800215 41
1793800220 41
1793800225 41
1793800230 41
1793800235 41
1793800240 41
1793800245 41
```
</details>

---

