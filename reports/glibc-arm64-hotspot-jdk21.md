---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1792141995 27
1792142000 27
1792142005 27
1792142010 27
1792142015 27
1792142020 27
1792142025 27
1792142030 27
1792142035 27
1792142040 27
1792142045 27
1792142050 27
1792142055 27
1792142060 25
1792142065 25
1792142070 25
1792142075 25
1792142080 25
1792142085 25
1792142090 25
```
</details>

---

