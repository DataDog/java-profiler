---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:46:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1793194955 16
1793194960 16
1793194965 16
1793194970 16
1793194975 16
1793194980 16
1793194985 16
1793194990 16
1793194995 16
1793195000 16
1793195005 16
1793195010 16
1793195015 16
1793195020 16
1793195025 16
1793195030 16
1793195035 16
1793195040 16
1793195045 16
1793195050 16
```
</details>

---

