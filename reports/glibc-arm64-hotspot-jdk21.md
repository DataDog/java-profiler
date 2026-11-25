---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 00:08:18 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 17-34 cores)</summary>

```
1795583073 17
1795583078 17
1795583083 17
1795583088 17
1795583093 17
1795583098 17
1795583103 17
1795583108 17
1795583113 17
1795583118 17
1795583123 17
1795583128 34
1795583133 34
1795583138 34
1795583143 34
1795583148 34
1795583153 34
1795583158 34
1795583163 34
1795583168 34
```
</details>

---

