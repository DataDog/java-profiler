---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:28:14 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 11 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792373017 48
1792373022 48
1792373027 43
1792373032 43
1792373037 43
1792373042 43
1792373047 43
1792373052 43
1792373057 43
1792373062 43
1792373067 43
1792373072 43
1792373077 43
1792373082 43
1792373087 48
1792373092 48
1792373097 48
1792373102 48
1792373107 48
1792373112 48
```
</details>

---

