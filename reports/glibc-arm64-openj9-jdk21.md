---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 12:40:40 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1793378185 45
1793378190 45
1793378195 45
1793378200 45
1793378205 45
1793378210 45
1793378215 45
1793378220 45
1793378225 40
1793378230 40
1793378235 43
1793378240 43
1793378245 43
1793378250 43
1793378255 43
1793378260 43
1793378265 43
1793378270 43
1793378275 43
1793378280 43
```
</details>

---

