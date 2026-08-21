---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-21 10:08:15 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 51-61 cores)</summary>

```
1787321101 61
1787321106 51
1787321111 51
1787321116 51
1787321121 51
1787321126 51
1787321131 51
1787321136 51
1787321141 51
1787321146 51
1787321151 51
1787321156 51
1787321161 51
1787321166 51
1787321171 51
1787321176 56
1787321181 56
1787321186 56
1787321191 56
1787321196 56
```
</details>

---

