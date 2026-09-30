---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 06:49:41 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 11 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790765079 40
1790765084 40
1790765089 40
1790765094 40
1790765099 40
1790765104 40
1790765109 40
1790765114 40
1790765119 40
1790765124 40
1790765129 40
1790765134 40
1790765139 45
1790765144 45
1790765149 45
1790765154 45
1790765159 45
1790765164 45
1790765169 45
1790765174 45
```
</details>

---

