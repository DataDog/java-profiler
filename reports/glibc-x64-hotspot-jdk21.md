---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 12:22:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1792426696 57
1792426701 57
1792426706 57
1792426711 59
1792426716 59
1792426721 59
1792426726 59
1792426731 59
1792426736 59
1792426741 59
1792426746 61
1792426751 61
1792426756 61
1792426761 61
1792426766 61
1792426771 61
1792426776 61
1792426781 59
1792426786 59
1792426791 59
```
</details>

---

