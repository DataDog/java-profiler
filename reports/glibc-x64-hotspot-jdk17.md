---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 07:23:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1793359108 70
1793359113 70
1793359118 70
1793359123 70
1793359128 70
1793359133 70
1793359138 70
1793359143 70
1793359148 70
1793359153 70
1793359158 70
1793359163 70
1793359168 70
1793359173 70
1793359178 70
1793359183 70
1793359188 70
1793359193 70
1793359198 70
1793359203 68
```
</details>

---

