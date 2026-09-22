---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093953 50
1790093958 50
1790093963 50
1790093968 50
1790093973 50
1790093978 50
1790093983 50
1790093988 50
1790093993 50
1790093998 50
1790094003 50
1790094008 50
1790094013 50
1790094018 50
1790094023 50
1790094028 50
1790094033 50
1790094038 50
1790094043 50
1790094048 50
```
</details>

---

