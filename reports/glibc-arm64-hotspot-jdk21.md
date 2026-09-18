---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 04:31:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 15 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789720022 43
1789720027 43
1789720032 43
1789720037 43
1789720042 43
1789720047 43
1789720052 43
1789720057 43
1789720062 43
1789720067 43
1789720072 43
1789720077 43
1789720082 43
1789720087 43
1789720092 48
1789720097 48
1789720102 48
1789720107 48
1789720112 48
1789720117 48
```
</details>

---

