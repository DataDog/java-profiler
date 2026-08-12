---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:29 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (5 unique values: 24-48 cores)</summary>

```
1786526152 25
1786526157 24
1786526162 24
1786526167 24
1786526172 24
1786526177 25
1786526182 25
1786526187 25
1786526192 25
1786526197 25
1786526202 25
1786526207 25
1786526212 25
1786526217 26
1786526222 26
1786526227 26
1786526232 26
1786526237 26
1786526242 26
1786526247 37
```
</details>

---

