---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 05:59:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 14 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793876082 30
1793876087 30
1793876092 30
1793876097 30
1793876102 30
1793876107 30
1793876112 30
1793876117 30
1793876122 30
1793876127 30
1793876132 30
1793876137 30
1793876142 30
1793876147 30
1793876152 30
1793876158 30
1793876163 30
1793876168 30
1793876173 30
1793876178 30
```
</details>

---

