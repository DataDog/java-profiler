---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 16:56:12 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 9 |
| Allocations | 205 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (6 unique values: 14-19 cores)</summary>

```
1792702115 19
1792702120 19
1792702125 19
1792702130 15
1792702135 15
1792702140 15
1792702145 15
1792702150 15
1792702155 15
1792702160 15
1792702165 15
1792702170 18
1792702175 18
1792702180 17
1792702185 17
1792702190 15
1792702195 15
1792702200 16
1792702205 16
1792702210 14
```
</details>

---

