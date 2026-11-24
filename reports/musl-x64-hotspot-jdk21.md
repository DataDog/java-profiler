---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 05:51:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1795517132 75
1795517137 75
1795517142 75
1795517147 75
1795517152 75
1795517157 75
1795517162 75
1795517167 75
1795517172 75
1795517177 75
1795517182 75
1795517187 75
1795517192 75
1795517197 75
1795517202 75
1795517207 75
1795517212 77
1795517217 77
1795517222 77
1795517227 77
```
</details>

---

