---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:07:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1793800903 44
1793800908 44
1793800913 44
1793800918 44
1793800923 44
1793800928 44
1793800933 44
1793800938 44
1793800943 44
1793800948 44
1793800953 44
1793800958 44
1793800963 44
1793800968 44
1793800973 44
1793800978 44
1793800983 44
1793800988 44
1793800993 44
1793800998 44
```
</details>

---

