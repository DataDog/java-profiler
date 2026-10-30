---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 19:51:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 9 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793404040 43
1793404045 43
1793404050 48
1793404055 48
1793404060 48
1793404065 48
1793404070 48
1793404075 48
1793404080 48
1793404085 48
1793404090 48
1793404095 48
1793404100 48
1793404105 48
1793404110 48
1793404115 48
1793404120 48
1793404125 48
1793404130 48
1793404135 48
```
</details>

---

