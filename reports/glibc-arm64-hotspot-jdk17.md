---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:11:55 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 14 |
| Allocations | 95 |

<details>
<summary>CPU Timeline (4 unique values: 32-48 cores)</summary>

```
1789743511 48
1789743516 48
1789743521 48
1789743526 48
1789743531 48
1789743536 48
1789743541 48
1789743546 48
1789743551 48
1789743556 48
1789743561 48
1789743566 48
1789743571 48
1789743576 48
1789743581 48
1789743586 48
1789743591 43
1789743596 43
1789743601 43
1789743606 43
```
</details>

---

