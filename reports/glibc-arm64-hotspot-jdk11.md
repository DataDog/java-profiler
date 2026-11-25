---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 00:08:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795583082 24
1795583087 24
1795583093 24
1795583098 24
1795583103 24
1795583108 24
1795583113 24
1795583118 24
1795583123 24
1795583128 24
1795583133 24
1795583138 29
1795583143 29
1795583148 29
1795583153 29
1795583158 34
1795583163 34
1795583168 34
1795583173 34
1795583178 34
```
</details>

---

