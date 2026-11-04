---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 75-76 cores)</summary>

```
1793800135 75
1793800140 75
1793800145 75
1793800150 75
1793800155 75
1793800160 75
1793800165 75
1793800170 75
1793800175 75
1793800180 75
1793800185 76
1793800190 76
1793800195 76
1793800200 76
1793800205 76
1793800210 76
1793800215 76
1793800220 76
1793800225 76
1793800230 76
```
</details>

---

