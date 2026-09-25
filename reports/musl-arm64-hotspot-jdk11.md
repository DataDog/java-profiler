---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:23:19 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790335139 48
1790335144 48
1790335149 48
1790335154 36
1790335159 36
1790335164 36
1790335169 36
1790335174 36
1790335179 36
1790335184 36
1790335189 36
1790335194 36
1790335199 36
1790335204 36
1790335209 36
1790335214 36
1790335219 36
1790335224 36
1790335229 36
1790335234 36
```
</details>

---

