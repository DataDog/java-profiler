---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 06:49:41 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790765061 40
1790765066 40
1790765071 40
1790765076 40
1790765081 40
1790765086 40
1790765091 40
1790765096 40
1790765101 40
1790765106 40
1790765111 40
1790765116 40
1790765121 40
1790765126 40
1790765131 40
1790765136 40
1790765141 45
1790765146 45
1790765151 45
1790765156 45
```
</details>

---

