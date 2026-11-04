---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
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
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1793800155 77
1793800160 77
1793800165 77
1793800170 77
1793800175 77
1793800180 77
1793800185 77
1793800190 77
1793800195 79
1793800200 79
1793800205 79
1793800210 79
1793800215 81
1793800220 81
1793800225 81
1793800230 81
1793800235 81
1793800240 81
1793800245 81
1793800250 81
```
</details>

---

