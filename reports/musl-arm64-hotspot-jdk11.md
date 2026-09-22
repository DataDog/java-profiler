---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:32:54 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 10-10 cores)</summary>

```
1790093938 10
1790093943 10
1790093948 10
1790093953 10
1790093958 10
1790093963 10
1790093968 10
1790093973 10
1790093978 10
1790093983 10
1790093988 10
1790093993 10
1790093998 10
1790094003 10
1790094008 10
1790094013 10
1790094018 10
1790094023 10
1790094028 10
1790094033 10
```
</details>

---

