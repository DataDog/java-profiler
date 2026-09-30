---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:59:07 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 12 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 13 |
| Allocations | 206 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790780122 43
1790780127 48
1790780132 48
1790780137 48
1790780142 48
1790780147 48
1790780152 48
1790780158 48
1790780163 48
1790780168 48
1790780173 48
1790780178 48
1790780183 48
1790780188 48
1790780193 48
1790780198 48
1790780203 48
1790780208 48
1790780213 48
1790780218 48
```
</details>

---

