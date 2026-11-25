---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:30:36 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1795631143 43
1795631149 43
1795631154 43
1795631159 43
1795631164 43
1795631169 43
1795631174 43
1795631179 43
1795631184 43
1795631189 43
1795631194 43
1795631199 43
1795631204 43
1795631209 48
1795631214 48
1795631219 42
1795631224 42
1795631229 42
1795631234 42
1795631239 42
```
</details>

---

