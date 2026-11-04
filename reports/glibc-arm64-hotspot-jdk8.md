---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 14:11:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 37-48 cores)</summary>

```
1793819150 48
1793819155 48
1793819160 48
1793819165 48
1793819170 48
1793819175 48
1793819180 48
1793819185 48
1793819190 48
1793819195 48
1793819200 48
1793819205 47
1793819210 47
1793819215 45
1793819220 45
1793819225 45
1793819230 46
1793819235 46
1793819240 46
1793819245 46
```
</details>

---

