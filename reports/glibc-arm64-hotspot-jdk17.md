---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:30:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 9 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (3 unique values: 28-34 cores)</summary>

```
1795631094 29
1795631099 29
1795631104 29
1795631109 29
1795631114 29
1795631119 29
1795631124 34
1795631129 34
1795631134 29
1795631139 29
1795631144 29
1795631149 29
1795631154 29
1795631159 29
1795631164 29
1795631169 29
1795631174 29
1795631179 29
1795631184 29
1795631189 29
```
</details>

---

