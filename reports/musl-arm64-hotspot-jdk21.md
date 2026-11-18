---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 43-51 cores)</summary>

```
1795001047 51
1795001052 51
1795001057 51
1795001062 43
1795001067 43
1795001072 43
1795001077 43
1795001082 43
1795001087 43
1795001092 43
1795001097 43
1795001102 43
1795001107 43
1795001112 43
1795001117 43
1795001122 43
1795001127 43
1795001132 43
1795001137 43
1795001142 43
```
</details>

---

