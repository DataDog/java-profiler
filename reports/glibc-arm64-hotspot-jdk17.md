---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 08:28:55 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 10 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 34-36 cores)</summary>

```
1793363089 36
1793363094 36
1793363099 36
1793363104 36
1793363109 36
1793363114 35
1793363119 35
1793363124 35
1793363129 35
1793363134 36
1793363139 36
1793363144 34
1793363149 34
1793363154 34
1793363159 34
1793363164 34
1793363169 34
1793363174 34
1793363179 34
1793363184 34
```
</details>

---

