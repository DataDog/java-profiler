---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-08 12:27:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 41-65 cores)</summary>

```
1775665097 41
1775665102 41
1775665107 41
1775665112 62
1775665117 62
1775665122 62
1775665127 62
1775665132 62
1775665137 62
1775665142 65
1775665147 65
1775665152 65
1775665157 65
1775665162 65
1775665167 65
1775665172 65
1775665177 65
1775665182 65
1775665187 65
1775665192 65
```
</details>

---

