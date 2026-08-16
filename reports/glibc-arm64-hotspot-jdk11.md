---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-16 11:16:13 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 9 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1786893108 18
1786893113 18
1786893118 18
1786893123 18
1786893128 18
1786893133 18
1786893138 18
1786893143 18
1786893148 18
1786893153 18
1786893158 18
1786893163 18
1786893168 13
1786893173 13
1786893178 13
1786893183 13
1786893188 13
1786893193 13
1786893198 13
1786893203 13
```
</details>

---

