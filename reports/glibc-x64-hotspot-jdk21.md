---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 58-63 cores)</summary>

```
1792141995 63
1792142000 63
1792142005 63
1792142010 63
1792142015 63
1792142020 63
1792142025 63
1792142030 63
1792142035 63
1792142040 61
1792142045 61
1792142050 61
1792142055 58
1792142060 58
1792142065 58
1792142070 58
1792142075 58
1792142080 58
1792142085 58
1792142090 58
```
</details>

---

